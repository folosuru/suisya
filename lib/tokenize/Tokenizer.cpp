#include "Tokenizer.hpp"

#include <cassert>
#include <cctype>
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <istream>
#include <optional>
#include <string>
#include <string_view>
#include <variant>

#include "Token.hpp"
#include "tokenize/util/StreamReader.hpp"

namespace Suisya {

namespace {
bool is_identifier(char c, bool is_front = false) {
    if (is_front) {
        return std::isalpha(c) || (c == '_');
    } else {
        return std::isalpha(c) || (c == '_') || std::isdigit(c);
    }
}

bool isSpace(int c) {
    return c == ' ' || c == '\t';
}

template<class StreamT>
bool skipLineBreak(StreamT& input) {
    int c = input.peek();
    if (c == '\r') {
        input.ignore(1);
        if (input.peek() == '\n') {
            input.ignore(1);
        }
    } else if (c == '\n') {
        input.ignore(1);
    } else {
        return false;
    }
    return true;
}

}

Tokenizer::Tokenizer(std::istream& input_, std::ostream& output_) : input(input_), output(output_) {}

Token Tokenizer::getScriptToken() {
    if (!std::holds_alternative<Token>(preread)) {
        readCancel();
        preread.emplace<Token>(getScriptToken_impl());

    } else {
    }
    return std::get<Token>(preread);
}

RawTextToken Tokenizer::getRawTextToken() {
    if (!std::holds_alternative<RawTextToken>(preread)) {
        readCancel();
        preread.emplace<RawTextToken>(getRawTextToken_impl());
    }
    return std::get<RawTextToken>(preread);
}

Token Tokenizer::getScriptToken_impl() {
    using traits = std::istream::traits_type;

    while (true) {  // skip whitespace
        auto current = input.peek();
        if (isSpace(current)) {
            input.ignore(1);
            continue;
        }
        if (skipLineBreak(input)) {
            onLineBreak();
            continue;
        }
        break;
    }

    auto delimiter = tryCreateDelimiter();
    if (delimiter) {
        return delimiter.value();
    }

    auto literal = tryCreateTextLiteralToken();
    if (literal) {
        return literal.value();
    }

    auto c = input.peek();
    if (is_identifier(traits::to_char_type(c), true)) {
        return createIdentifier();
    }

    if (c == traits::eof()) {
        return Token::createEOFToken();
    }
    return Token::createDelimiter(Token::TokenType::Illegal, {0, 0, 0}, 0);
}

void Tokenizer::readCancel() {
    input.restoreBuffer();
}

Token Tokenizer::createIdentifier() {
    SourcePosition pos = input.getCurrentPos();
    size_t len = 0;
    while (true) {
        auto next = input.peek();

        using trait = std::istream::traits_type;
        if (trait::eof() == next) {
            break;
        }

        auto next_char = trait::to_char_type(next);

        if (!is_identifier(next_char)) {
            break;
        }
        len++;
        input.ignore(1);
    }
    return Token::createIdentifyer(pos, len, getsource());
}

std::optional<Token> Tokenizer::tryCreateDelimiter() {
    SourcePosition pos = input.getCurrentPos();
    int c = input.peek();
    if (c == '=') {
        input.ignore();
        return Token::createDelimiter(Token::TokenType::Equal, pos, 1);
    } else if (c == ';') {
        input.ignore();
        return Token::createDelimiter(Token::TokenType::Semicolon, pos, 1);
    } else if (c == '.') {
        input.ignore();
        return Token::createDelimiter(Token::TokenType::Dot, pos, 1);
    }
    return std::nullopt;
}

std::optional<Token> Tokenizer::getIfKeyword(KeywordType type) {
    Token t = getScriptToken();
    if (t.type == Token::TokenType::Keyword && t.data.keyword_type == type) {
        return t;
    }
    return std::nullopt;
}

std::optional<RawTextToken> Tokenizer::tryCreateDollarToken(char peek_result) {
    SourcePosition pos = input.getCurrentPos();
    if (peek_result != '$') {
        return std::nullopt;
    }
    input.ignore(1);
    if (input.peek() == '$') {
        input.ignore(1);
        return RawTextToken::createDelimiter(RawTextToken::TokenType::DoubleDollar, pos, 2);
    } else {
        return RawTextToken::createDelimiter(RawTextToken::TokenType::Dollar, pos, 1);
    }
}

std::optional<Token> Tokenizer::tryCreateTextLiteralToken() {
    using trait = std::istream::traits_type;
    if (input.peek() != '\"') {
        return std::nullopt;
    }
    input.ignore(1);
    SourcePosition pos = input.getCurrentPos();
    size_t len = 0;
    while (true) {
        if (skipLineBreak(input)) {
            onLineBreak();
            len++;
            continue;
        }

        auto peek_char = input.peek();
        if (peek_char == trait::eof()) {
            break;
        }
        if (peek_char == '\"') {
            input.ignore(1);
            break;
        }
        len++;
        input.ignore(1);
    }
    return Token::createDelimiter(Token::TokenType::TextLiteral, pos, len);
}

std::optional<RawTextToken> Tokenizer::tryCreateReturnToken(char peek_result) {
    SourcePosition pos = input.getCurrentPos();
    if (peek_result == '\r') {
        input.ignore(1);
        if (input.peek() == '\n') {
            input.ignore(1);
        }
    } else if (peek_result == '\n') {
        input.ignore(1);
    } else {
        return std::nullopt;
    }

    auto result = RawTextToken::createLineBreak(pos);
    return result;
}

// read char if not $
RawTextToken Tokenizer::getRawTextToken_impl() {
    using trait = std::istream::traits_type;
    SourcePosition src_pos = input.getCurrentPos();
    size_t len = 0;

    auto next = input.peek();
    if (next == trait::eof()) {
        return RawTextToken::createEOFToken();  // EOF Token
    }

    if (auto return_node = tryCreateReturnToken(trait::to_char_type(next)); return_node) {
        return return_node.value();
    }

    if (auto dollar = tryCreateDollarToken(trait::to_char_type(next)); dollar) {
        return dollar.value();
    }

    while (true) {
        // need to make other token
        if (next == '$' || next == '\r' || next == '\n') {
            break;
        }

        // chech $

        input.ignore();
        len++;

        next = input.peek();
        if (next == trait::eof()) {
            break;
        }
    }
    if (len == 0) {
        // something went wrong
    }
    return RawTextToken::createText(len, src_pos);
}

bool Tokenizer::isEndOfScriptToken() {
    auto c = input.peek();
    return (c == ' ' || c == '\r' || c == '\n' || c == '\t');
}

void Tokenizer::onLineBreak() {}

void Tokenizer::nextToken() {
    input.clearBuffer();
    preread = std::nullopt;
}

std::string_view Tokenizer::getView(const Token& t) const {
    return std::string_view{getsource()}.substr(t.start, t.len);
}
}
