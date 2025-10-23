#pragma once
#ifndef SUISHYA_COMPILECONTEXT_H
#define SUISHYA_COMPILECONTEXT_H

#include <list>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#include "script/value/ValueBase.hpp"

namespace Suisya {

class Variable {
public:
    const ValueBase& get() const {
        return value;
    }

    Variable(ValueBase b) : value(b) {}

private:
    ValueBase value;
};

class CompileContext {
public:
    std::optional<const Variable*> getSymbol(std::string_view) const;
    void addSymbol(std::string_view name, ValueBase value);
    bool toplevel_node = true;

private:
    std::unordered_map<std::string_view, std::unique_ptr<Variable>> idetifier_map;
    std::list<std::string> idetifier_string;
};
}

#endif  // SUISHYA_COMPILECONTEXT_H1
