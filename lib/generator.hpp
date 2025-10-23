#pragma once

#ifndef SUISHYA_GENERATOR_HPP_
#define SUISHYA_GENERATOR_HPP_

#include <istream>

#include "error/ErrorReport.hpp"

namespace Suisya {
void generate(std::istream& input, std::ostream& output, const ErrorReportFunc_t& error_report);
}
#endif  // SUISHYA_GENERATOR_HPP_
