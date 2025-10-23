#include "Statement.hpp"

#include <cstdio>
#include <iostream>
#include <optional>
#include <string_view>

#include "Literal.hpp"
#include "Token.hpp"
#include "error/ErrorReport.hpp"
#include "script/utility.hpp"
#include "script/value/ValueBase.hpp"

namespace Suisya {

NodeExecResult LetNode::exec(Tokenizer &tokenizer, CompileContext &ctx, const ErrorReportFunc_t &err) {
    auto let_token = tokenizer.getIfKeyword(Keyword_let);
    if (!let_token) {
        return std::nullopt;
    }
    tokenizer.nextToken();

    auto name_token = tokenizer.getScriptToken();
    if (name_token.type != Token::TokenType::Identifier) {
        err(SyntaxError{"need Identifier"});
        return std::nullopt;
    }
    tokenizer.nextToken();

    std::string_view name_view = tokenizer.getView(name_token);

    auto item = ctx.getSymbol(name_view);

    if (item) {
        return std::nullopt;
    }

    auto eq = tokenizer.getScriptToken();
    if (eq.type != Token::TokenType::Equal) {
        return std::nullopt;
    }

    tokenizer.nextToken();

    auto result = TextLiteral::exec(tokenizer, ctx, err);
    if (result) {
        ctx.addSymbol(name_view, result.value());
        return ValueBase(ValueBase::Type::void_type);
    }
    return std::nullopt;
}

}
