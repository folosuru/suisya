#pragma once
#ifndef SUISYA_SCRIPT_STATEMENT_LITERAL_HPP
#define SUISYA_SCRIPT_STATEMENT_LITERAL_HPP
#include "error/ErrorReport.hpp"
#include "script/CompileContext.hpp"
#include "script/utility.hpp"
#include "tokenize/Tokenizer.hpp"

namespace Suisya {

namespace TextLiteral {
NodeExecResult exec(Tokenizer &tokenizer, CompileContext &ctx, const ErrorReportFunc_t &err);

}

}
#endif  // SUISYA_SCRIPT_STATEMENT_LITERAL_HPP1
