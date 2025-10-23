#include "ValueBase.hpp"

#include <optional>
#include <string>

#include "error/ErrorReport.hpp"
#include "script/value/ContentValue.hpp"

namespace Suisya {

ValueBase ValueBase::fromContent(ContentValue* v) {
    ValueBase result;
    result.value.content_v = v;
    result.type = Type::content_type;
    return result;
}

ValueBase ValueBase::fromInt(int32_t v) {
    ValueBase result;
    result.value.int_v = v;
    result.type = Type::int_type;
    return result;
}

ContentValue* ValueBase::getContent() const noexcept {
    if (type == Type::content_type) {
        return value.content_v;
    } else if (type == Type::int_type) {
        return new InlineTextContent(std::to_string(value.int_v));
    }
    return nullptr;
}

std::optional<ValueBase> ValueBase::member(std::string_view name, const ErrorReportFunc_t& err_func) {
    switch (type) {
        case Type::int_type:
            return fromInt(value.int_v + 1);
            break;
        case Type::float_type:
            break;
        case Type::content_type:
            if (name == "len") {
                return fromInt(value.content_v->getExceptLength());
            }
            break;
        case Type::unresolve:
            break;
        case Type::void_type:
            break;
    }
    err_func(SyntaxError{"Type error..."});
    return std::nullopt;
}
}
