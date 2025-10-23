#pragma once
#include <functional>
#include <string_view>
#include <variant>
#ifndef SUISUA_ERROR_ERRORREPORT_HPP
#define SUISUA_ERROR_ERRORREPORT_HPP

namespace Suisya {

struct SyntaxError {
    std::string_view message;
};

class ErrorReport {
public:
    ErrorReport(const SyntaxError& err);

    std::variant<SyntaxError> error;
};

using ErrorReportFunc_t = std::function<void(ErrorReport)>;

}

#endif  // SUISUA_ERROR_ERRORREPORT_HPP1
