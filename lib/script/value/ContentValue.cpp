#include "ContentValue.hpp"

#include <iostream>
#include <string_view>

namespace Suisya {

void RawTextSpanContent::append(std::string& buffer) const {
    buffer += std::string_view(source).substr(start_pos, len);
}

void RawTextSpanContent::output(std::ostream& output) const {
    output << std::string_view(source).substr(start_pos, len);
}
}
