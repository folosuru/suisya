#pragma once
#include <variant>
#ifndef SUISHYA_TOKENIZER_HPP
#define SUISHYA_TOKENIZER_HPP
#include <cstddef>
#include <deque>
#include <iosfwd>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#include "Token.hpp"
#include "tokenize/StreamReader.hpp"

namespace Suisya {

class Tokenizer {
public:
    Tokenizer(std::istream& input_, std::ostream& output_);

    Token getScriptToken();
    void readCancel();
    void nextToken();

    std::optional<Token> getIfKeyword(KeywordType type);

    RawTextToken getRawTextToken();

    bool isEndOfScriptToken();

    std::string_view getView(const Token& t) const;

    const std::string& getsource() const noexcept {
        return input.getSource();
    }

private:
    StreamReader input;
    std::ostream& output;
    using Token_id = size_t;

    std::variant<Token, RawTextToken, std::nullopt_t> preread = std::nullopt;

    std::optional<RawTextToken> tryCreateReturnToken(char peek_result);
    std::optional<RawTextToken> tryCreateDollarToken(char peek_result);
    std::optional<Token> tryCreateTextLiteralToken();
    Token createIdentifier();
    std::optional<Token> tryCreateDelimiter();

    void onLineBreak();

    RawTextToken getRawTextToken_impl();
    Token getScriptToken_impl();
};
}

#endif  //
