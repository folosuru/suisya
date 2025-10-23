#pragma once

#include <cstddef>
#include <deque>

#include "Token.hpp"
#ifndef SUISYA_TOKENIZE_STREAMREADER_HPP
#define SUISYA_TOKENIZE_STREAMREADER_HPP
#include <iosfwd>
#include <queue>

namespace Suisya {

class StreamReader {
public:
    explicit StreamReader(std::istream& input_) : input(input_) {
        pos_to_line.push_back(0);
    }

    StreamReader() = delete;

    [[nodiscard]] int peek();
    void ignore(int c = 1);

    void clearBuffer();

    // peek()時にBufferに記録されている部分を
    // 読み出すようにする
    void restoreBuffer();

    SourcePosition getCurrentPos() const noexcept;

    const std::string& getSource() const noexcept {
        return source;
    }

private:
    std::deque<char> current_buffer;

    std::queue<char> reading_buffer;
    std::istream& input;

    size_t current_line_len;
    void appendSource(int c);
    void updateBufferPos(int c);

    std::string source;
    std::deque<size_t> pos_to_line;
};

}

#endif  // SUISYA_TOKENIZE_STREAMREADER_HPP
