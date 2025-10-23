#ifndef SUISHYA_TOKEN_H
#define SUISHYA_TOKEN_H

#include <cstddef>
#include <string>

namespace Suisya {
enum KeywordType {
    Keyword_let
};

union TokenData {
    int number;
    enum KeywordType keyword_type;
};

/**
 * position in source
 * all number start by 0
 *
 */
struct SourcePosition {
    const size_t line_count;
    const size_t line_pos;
    const size_t text_offset;

    SourcePosition(size_t line_count_, size_t line_pos_, size_t text_offset_)
        : line_count(line_count_), line_pos(line_pos_), text_offset(text_offset_) {}
};

inline bool operator==(const Suisya::SourcePosition& p1, const Suisya::SourcePosition& p2) {
    return (p1.line_count == p2.line_count) && (p1.line_pos == p2.line_pos) && (p1.text_offset == p2.text_offset);
}

struct Token {
    enum class TokenType;
    const TokenType type;
    union TokenData data;
    SourcePosition pos;
    const size_t start;
    const size_t len;
    // const FILE_TYPE_T file;

    enum class TokenType {
        Plus,          // +
        Minus,         // -
        Star,          // *
        Slash,         // /
        LeftParen,     // (
        RightParen,    // )
        Semicolon,     // ;
        Colon,         // :
        DoubleQuote,   // "
        Dollar,        // $
        DoubleDollar,  // $$
        Exclamation,   // !
        Greater,       // >
        GreaterOrEq,   // >=
        Lesser,        // <
        LesserOrEq,    // <=
        Equal,         // =
        Dot,           // .
        Keyword,       // let
        Number,        // [0-9]*
        TextLiteral,   // "something"
        Identifier,    // [A-Z | a-z | 0-9 | _]
        Token_EOF,     // End of source
        Illegal,
        TokenType_None
    };

    static Token createEOFToken();
    static Token createIdentifyer(SourcePosition src_pos, size_t len, const std::string& source);
    static Token createDelimiter(TokenType t, SourcePosition pos, size_t len);

    Token(const TokenType type_, union TokenData data_, SourcePosition pos_, const size_t start_, const size_t len_)
        : type(type_), data(data_), pos(pos_), start(start_), len(len_) {}
};

struct RawTextToken {
    enum class TokenType {
        Text,
        LineBreak,
        Dollar,
        DoubleDollar,
        Token_EOF
    };
    const TokenType type;
    SourcePosition pos;
    const size_t start;
    const size_t len;

    static RawTextToken createEOFToken();
    static RawTextToken createText(size_t len, SourcePosition pos);
    static RawTextToken createLineBreak(SourcePosition pos);
    static RawTextToken createDelimiter(TokenType t, SourcePosition pos, size_t len_);

    RawTextToken(TokenType type_, SourcePosition pos_, const size_t start_, const size_t len_)
        : type(type_), pos(pos_), start(start_), len(len_) {}
};
}

#endif  // SUISHYA_TOKEN_H
