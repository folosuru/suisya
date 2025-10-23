#pragma once

#ifndef SUISYA_SCRIPT_VALUEBASE_HPP
#define SUISYA_SCRIPT_VALUEBASE_HPP

#include <cstddef>
#include <cstdint>
#include <iosfwd>
#include <optional>
#include <string>
#include <string_view>

#include "error/ErrorReport.hpp"

namespace Suisya {

class ContentValue {
public:
    virtual ~ContentValue() = default;
    virtual size_t getExceptLength() const = 0;
    virtual void append(std::string& buffer) const = 0;
    virtual void output(std::ostream& output) const = 0;
};

class ValueBase {
public:
    enum class Type {
        int_type,
        float_type,
        content_type,
        unresolve,
        void_type
    };

    Type getType() const noexcept {
        return type;
    }

    auto getInt() const noexcept {
        return value.int_v;
    }

    auto getFloat() const noexcept {
        return value.float_v;
    }

    ContentValue* getContent() const noexcept;

    static ValueBase fromContent(ContentValue* v);
    static ValueBase fromInt(int32_t);

    std::optional<ValueBase> member(std::string_view name, const ErrorReportFunc_t& f);

    ValueBase(Type t) : type(t) {}

private:
    union {
        int32_t int_v;
        double float_v;
        ContentValue* content_v;

    } value;

    ValueBase() = default;
    Type type;
};

}

#endif  // SUISYA_SCRIPT_VALUEBASE_HPP
