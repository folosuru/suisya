#include "RootNode.hpp"

#include <string>

#include "CompileContext.hpp"
#include "Token.hpp"
#include "error/ErrorReport.hpp"
#include "script/statement/Statement.hpp"
#include "script/statement/ValueNode.hpp"
#include "script/value/ContentValue.hpp"
#include "script/value/ValueBase.hpp"

namespace Suisya {
ValueBase RootNode::exec(Tokenizer &tokenizer, CompileContext &ctx, const ErrorReportFunc_t &err) {
    auto v = [&]() {
        auto d = LetNode::exec(tokenizer, ctx, err);
        if (d) {
            return d.value();
        }
        if (auto expr = node::expr(tokenizer, ctx, err)) {
            return expr.value();
        }

        std::string &s = *new std::string("yo");
        return ValueBase::fromContent(new RawTextSpanContent(s, 0, 3));
    }();
    auto t = tokenizer.getScriptToken();
    if (t.type == Token::TokenType::Semicolon) {
        tokenizer.nextToken();
    } else {
        tokenizer.readCancel();
    }
    return v;
}
}
