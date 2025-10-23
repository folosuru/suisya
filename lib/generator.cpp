#include "generator.hpp"

#include <string_view>

#include "Token.hpp"
#include "Tokenizer.hpp"
#include "error/ErrorReport.hpp"
#include "script/CompileContext.hpp"
#include "script/RootNode.hpp"
#include "script/value/ValueBase.hpp"

namespace Suisya {
void generate(std::istream& input, std::ostream& output, const ErrorReportFunc_t& error_report) {
    Tokenizer tokenizer(input, output);
    CompileContext ctx;

    enum class line_state {
        line_start,
        only_scirpt,
        content
    };
    line_state line_stat = line_state::line_start;

    while (true) {
        RawTextToken t = tokenizer.getRawTextToken();
        tokenizer.nextToken();
        switch (t.type) {
            case RawTextToken::TokenType::Token_EOF: {
                return;
            }
            case RawTextToken::TokenType::Text: {
                output << std::string_view(tokenizer.getsource()).substr(t.start, t.len);
                line_stat = line_state::content;
                break;
            }
            case RawTextToken::TokenType::DoubleDollar: {
                output << "$";
                line_stat = line_state::content;
                break;
            }
            case RawTextToken::TokenType::LineBreak: {
                if (line_stat != line_state::only_scirpt) {
                    output << '\r' << '\n';
                }
                line_stat = line_state::line_start;
                break;
            }
            case RawTextToken::TokenType::Dollar: {
                auto v = RootNode::exec(tokenizer, ctx, error_report);
                auto content = v.getContent();
                if (content != nullptr) {
                    content->output(output);
                    line_stat = line_state::content;
                } else {
                    line_stat = line_state::only_scirpt;
                }

                break;
            }

            default:
                break;
        }
    }
}
}
