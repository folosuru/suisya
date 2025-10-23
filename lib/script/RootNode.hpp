#pragma once
#include "CompileContext.hpp"
#include "error/ErrorReport.hpp"
#ifndef SUISYA_SCRIPT_ROOTNODE_HPP
#define SUISYA_SCRIPT_ROOTNODE_HPP
#include "Tokenizer.hpp"
#include "value/ValueBase.hpp"

namespace Suisya {
class RootNode {
public:
    static ValueBase exec(Tokenizer &tokenizer, CompileContext &ctx, const ErrorReportFunc_t &err);
};
}

#endif  // PLEXPROC_SCRIPT_ROOTNODE_HPP
