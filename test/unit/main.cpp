

#include <Tokenizer.hpp>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <sstream>

#include "Token.hpp"
void testStreamReader();

int main() {
    testStreamReader();
    {
        std::string str = "hello $\r\n$$ world\n";
        std::cout << "input:\n" << str << "\n" << std::endl;
        std::stringstream ss(str);
        Suisya::Tokenizer tokenizer(ss, std::cout);
        Suisya::RawTextToken::TokenType correct_token[] = {
            Suisya::RawTextToken::TokenType::Text,      Suisya::RawTextToken::TokenType::Dollar,
            Suisya::RawTextToken::TokenType::LineBreak, Suisya::RawTextToken::TokenType::DoubleDollar,
            Suisya::RawTextToken::TokenType::Text,      Suisya::RawTextToken::TokenType::LineBreak,
            Suisya::RawTextToken::TokenType::Token_EOF};

        int token_cnt = -1;
        while (true) {
            auto t1 = tokenizer.getRawTextToken();

            tokenizer.nextToken();

            token_cnt++;
            if (t1.type == Suisya::RawTextToken::TokenType::Token_EOF) {
                std::cout << "EOF" << "\n";
                break;
            }
            if (t1.type == Suisya::RawTextToken::TokenType::LineBreak) {
                std::cout << "[LF]\n";
                continue;
            }

            std::cout << "\"" << tokenizer.getsource().substr(t1.start, t1.len) << "\"\n";

            if (t1.type != correct_token[token_cnt]) {
                std::cout << "error in token " << token_cnt << ": expect " << static_cast<int>(correct_token[token_cnt])
                          << "but" << static_cast<int>(t1.type) << "\n";
                return 1;
            }
        }
    }

    std::string source2 = "letitbe let world";
    std::istringstream ss2(source2);
    Suisya::Tokenizer tokenizer2(ss2, std::cout);
    {
        auto t = tokenizer2.getScriptToken();
        assert(tokenizer2.getView(t) == "letitbe");
        tokenizer2.nextToken();
    }

    {
        auto t2 = tokenizer2.getScriptToken();
        assert(t2.type == Suisya::Token::TokenType::Keyword);
        assert(tokenizer2.getView(t2) == "let");
        std::cout << tokenizer2.getsource().substr(t2.start, t2.len) << ", " << static_cast<int>(t2.type) << "\n";
        tokenizer2.nextToken();
    }
    {
        auto raw_token = tokenizer2.getRawTextToken();
        assert(tokenizer2.getsource().substr(raw_token.start, raw_token.len) == " world");
    }
}
