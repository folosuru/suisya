#include <cassert>
#include <iostream>
#include <sstream>
#include <tokenize/StreamReader.hpp>

#include "Token.hpp"

void testStreamReader() {
    std::string src = "QWERTY";
    std::stringstream ss(src);
    Suisya::StreamReader reader(ss);

    Suisya::SourcePosition p = {0, 0, 0};
    assert(reader.getCurrentPos() == p);

    assert(reader.peek() == 'Q');  // | QWERTY
    reader.ignore();               // Q | WERTY
    reader.clearBuffer();

    assert(reader.getCurrentPos().line_count == 0);
    assert(reader.getCurrentPos().line_pos == 1);
    assert(reader.getCurrentPos().text_offset == 1);

    assert(reader.peek() == 'W');  // | WERTY
    reader.ignore();
    assert(reader.peek() == 'E');  // W | ERTY
    reader.ignore();               // WE | RTY
    reader.restoreBuffer();
    assert(reader.peek() == 'W');  // | WERTY
    reader.ignore();
    assert(reader.peek() == 'E');  // W | ERTY
    reader.ignore();

    assert(reader.getCurrentPos().line_count == 0);
    assert(reader.getCurrentPos().line_pos == 3);
    assert(reader.getCurrentPos().text_offset == 3);
    assert(reader.peek() == 'R');  // WE | RTY
    reader.ignore();
    assert(reader.peek() == 'T');  // WER | TY
    reader.ignore();               // WERT | Y
    reader.clearBuffer();          //  | Y
    assert(reader.peek() == 'Y');  //
    reader.ignore();               //  Y |
    reader.restoreBuffer();        //  | Y
    assert(reader.peek() == 'Y');
}
