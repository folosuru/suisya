#include "ValueNode.hpp"

#include <cstdio>
#include <optional>
#include <type_traits>

#include "script/utility.hpp"
#include "script/value/ValueBase.hpp"
#include "tokenize/Token.hpp"

namespace Suisya {

namespace node {
NodeExecResult expr(Tokenizer &tokenizer, CompileContext &ctx, const ErrorReportFunc_t &err) {
    return member(tokenizer, ctx, err);
}

NodeExecResult member_access(NodeExecResult result, Tokenizer &tokenizer, CompileContext &ctx,
                             const ErrorReportFunc_t &err) {
    auto next = tokenizer.getScriptToken();
    if (next.type == Token::TokenType::Identifier) {
        auto v = result->member(tokenizer.getView(next), err);
        if (v) {
            tokenizer.nextToken();
            return v;
        }
        tokenizer.readCancel();
    }
    return result;
}

NodeExecResult member(Tokenizer &tokenizer, CompileContext &ctx, const ErrorReportFunc_t &err) {
    NodeExecResult item = identifier(tokenizer, ctx, err);
    do {
        if (!item) {
            return item;
        }
        if (ctx.toplevel_node) {
            if (tokenizer.isEndOfScriptToken()) {
                return item;
            }
        }
        auto next = tokenizer.getScriptToken();
        if (next.type == Token::TokenType::Dot) {  // something.foo
            if (ctx.toplevel_node && tokenizer.isEndOfScriptToken()) {
                return item;
            }
            tokenizer.nextToken();
            item = member_access(item, tokenizer, ctx, err);
        } else {
            return item;
        }
    } while (true);
}

NodeExecResult identifier(Tokenizer &tokenizer, CompileContext &ctx, const ErrorReportFunc_t &err) {
    auto name = tokenizer.getScriptToken();
    if (name.type != Token::TokenType::Identifier) {
        return std::nullopt;
    }

    tokenizer.nextToken();

    auto name_view = tokenizer.getView(name);
    if (auto item = ctx.getSymbol(name_view); item) {
        return (item.value())->get();
    }
    return std::nullopt;
}
}

}
