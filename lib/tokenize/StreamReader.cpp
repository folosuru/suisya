#include "StreamReader.hpp"

#include <cstddef>
#include <cstdio>
#include <istream>

#include "Token.hpp"

namespace Suisya {

int StreamReader::peek() {
    if (reading_buffer.empty()) {
        return input.peek();
    }

    return reading_buffer.front();
}

void StreamReader::appendSource(int c) {
    if (c == '\n') {
        // CRLF
        if (!source.empty() && source.back() == '\r') {
            pos_to_line.pop_back();
        }
    }
    source += std::istream::traits_type::to_char_type(c);

    if (c == '\r' || c == '\n') {
        pos_to_line.push_back(source.size());
        current_line_len = 0;
    }
}

SourcePosition StreamReader::getCurrentPos() const noexcept {
    const size_t buffer_pos = source.size() - reading_buffer.size();
    size_t line;
    for (auto i = pos_to_line.rbegin();; i++) {
        if (*i <= buffer_pos) {
            line = *i;
            break;
        }
    }

    return SourcePosition(line, buffer_pos - line, buffer_pos);
}

void StreamReader::ignore(int c) {
    using trait = std::istream::traits_type;
    int i = 0;
    for (; i < c; i++) {
        if (reading_buffer.empty()) {
            break;
        }
        auto front = reading_buffer.front();
        current_buffer.push_back(front);
        reading_buffer.pop();
    }

    for (; i < c; i++) {
        auto next = input.peek();
        if (trait::eof() == next) {
            break;
        }

        appendSource(next);
        current_buffer.push_back(trait::to_char_type(next));
        input.ignore(1);
    }
}

void StreamReader::clearBuffer() {
    current_buffer.clear();
}

void StreamReader::restoreBuffer() {
    while (!current_buffer.empty()) {
        reading_buffer.push(current_buffer.front());
        current_buffer.pop_front();
    }
}
}
