#include "CompileContext.hpp"

#include <cstdio>
#include <memory>
#include <optional>
#include <string>
#include <string_view>

namespace Suisya {

std::optional<const Variable*> CompileContext::getSymbol(std::string_view name) const {
    auto i = idetifier_map.find(name);
    if (i != idetifier_map.end()) {
        return i->second.get();
    }
    return std::nullopt;
}

void CompileContext::addSymbol(std::string_view name, ValueBase value) {
    idetifier_string.push_back(std::string(name));
    auto& str = idetifier_string.back();
    auto variable = std::make_unique<Variable>(value);
    idetifier_map.emplace(std::string_view{str}, std::move(variable));
}
}
