#include "Token.hpp"

#include <string>
#include <string_view>

namespace Suisya {

RawTextToken RawTextToken::createLineBreak(SourcePosition pos) {
    return RawTextToken(TokenType::LineBreak, pos, pos.text_offset, 1);
}

RawTextToken RawTextToken::createDelimiter(TokenType t, SourcePosition pos, size_t len) {
    return RawTextToken(t, pos, pos.text_offset, len);
}

Token Token::createDelimiter(TokenType t, SourcePosition pos, size_t len) {
    return Token(t, {}, pos, pos.text_offset, len);
}

RawTextToken RawTextToken::createEOFToken() {
    return RawTextToken(TokenType::Token_EOF, {0, 0, 0}, 0, 0);
}

RawTextToken RawTextToken::createText(size_t len_, SourcePosition pos_) {
    return RawTextToken(TokenType::Text, pos_, pos_.text_offset, len_);
}

namespace {

using namespace std::string_view_literals;
constexpr std::pair<std::string_view, KeywordType> keywords[] = {{"let"sv, KeywordType::Keyword_let}};
}

Token Token::createIdentifyer(SourcePosition src_pos, size_t len, const std::string& source) {
    std::string_view Identifier_keyword = std::string_view{source}.substr(src_pos.text_offset, len);
    for (const auto& i : keywords) {
        if (i.first == Identifier_keyword) {
            TokenData data;
            data.keyword_type = KeywordType::Keyword_let;
            return Token(TokenType::Keyword, data, src_pos, src_pos.text_offset, len);
        }
    }
    return Token(Token::TokenType::Identifier, {}, src_pos, src_pos.text_offset, len);
}

Token Token::createEOFToken() {
    return Token(TokenType::Token_EOF, {}, {0, 0, 0}, 0, 0);
}
}
