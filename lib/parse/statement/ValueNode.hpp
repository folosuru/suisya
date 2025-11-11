#pragma once

#ifndef SUISYA_SCRIPT_STATEMENT_VALUENODE_HPP
#define SUISYA_SCRIPT_STATEMENT_VALUENODE_HPP
#include "error/ErrorReport.hpp"
#include "script/CompileContext.hpp"
#include "script/utility.hpp"
#include "tokenize/Tokenizer.hpp"

namespace Suisya {

namespace node {
NodeExecResult expr(Tokenizer &tokenizer, CompileContext &ctx, const ErrorReportFunc_t &err);
NodeExecResult member(Tokenizer &tokenizer, CompileContext &ctx, const ErrorReportFunc_t &err);

NodeExecResult identifier(Tokenizer &tokenizer, CompileContext &ctx, const ErrorReportFunc_t &err);
}

}

#endif  // SUISYA_SCRIPT_STATEMENT_VALUENODE_HPP1
