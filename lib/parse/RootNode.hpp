#pragma once
#include "error/ErrorReport.hpp"
#include "script/CompileContext.hpp"
#ifndef SUISYA_SCRIPT_ROOTNODE_HPP
#define SUISYA_SCRIPT_ROOTNODE_HPP
#include "script/value/ValueBase.hpp"
#include "tokenize/Tokenizer.hpp"

namespace Suisya {
class RootNode {
public:
    static ValueBase exec(Tokenizer &tokenizer, CompileContext &ctx, const ErrorReportFunc_t &err);
};
}

#endif  // PLEXPROC_SCRIPT_ROOTNODE_HPP
