#include "Literal.hpp"

#include <optional>

#include "script/value/ContentValue.hpp"
#include "script/value/ValueBase.hpp"
#include "tokenize/Token.hpp"
#include "tokenize/Tokenizer.hpp"

namespace Suisya {

NodeExecResult TextLiteral::exec(Tokenizer &tokenizer, CompileContext &ctx, const ErrorReportFunc_t &err) {
    auto t = tokenizer.getScriptToken();
    if (t.type != Token::TokenType::TextLiteral) {
        tokenizer.readCancel();
        return std::nullopt;
    }
    tokenizer.nextToken();
    auto content = new RawTextSpanContent(tokenizer.getsource(), t.start, t.len);
    return ValueBase::fromContent(content);
}
}
