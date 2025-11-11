#pragma once
#include "error/ErrorReport.hpp"
#include "script/CompileContext.hpp"
#include "script/utility.hpp"
#include "tokenize/Tokenizer.hpp"
#ifndef SUISYA_SCRIPT_STATEMENT_STATEMENT_HPP
#define SUISYA_SCRIPT_STATEMENT_STATEMENT_HPP

namespace Suisya {

namespace LetNode {
NodeExecResult exec(Tokenizer &tokenizer, CompileContext &ctx, const ErrorReportFunc_t &err);
}
}
#endif  // SUISYA_SCRIPT_STATEMENT_STATEMENT_HPP1
