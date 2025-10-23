#pragma once

#include <cstddef>

#ifndef SUISYA_SCRIPT_VALUE_CONTENTVALUE_HPP
#define SUISYA_SCRIPT_VALUE_CONTENTVALUE_HPP
#include <string>

#include "ValueBase.hpp"

namespace Suisya {

class RawTextSpanContent : public ContentValue {
public:
    RawTextSpanContent(const std::string& source_, size_t start, size_t len_)
        : source(source_), start_pos(start), len(len_) {}

    ~RawTextSpanContent() override = default;

    size_t getExceptLength() const override {
        return len;
    }

    void append(std::string& buffer) const override;
    void output(std::ostream& output) const override;

private:
    const std::string& source;
    size_t start_pos;
    size_t len;
};

class InlineTextContent : public ContentValue {
public:
    InlineTextContent(std::string str) : text(str) {}

    ~InlineTextContent() override = default;

    size_t getExceptLength() const override {
        return text.length();
    }

    void append(std::string& buffer) const override {
        buffer += text;
    }

    void output(std::ostream& output) const override {
        output << text;
    }

private:
    std::string text;
};
}

#endif  // SUISYA_SCRIPT_VALUE_CONTENTVALUE_HPP
