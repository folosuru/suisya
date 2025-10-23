#include <fstream>
#include <iostream>

constexpr char sep[] = "====================\n";

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }
    std::ifstream in(argv[1]);

    std::string cmd_in, file_in;
    int line = 0;
    while (true) {
        line++;
        bool cmd_flag = static_cast<bool>(std::getline(std::cin, cmd_in));
        bool file_flag = static_cast<bool>(std::getline(in, file_in));
        if (!cmd_flag || !file_flag) {
            if (cmd_flag == file_flag) return 0;

            std::cerr << sep << "lines count not match\n"
                      << "in line " << line << "\n"
                      << sep << std::endl;
            return 1;
        }

        if (file_in != cmd_in) {
            std::cerr << sep << "line different in line " << line << "\n"
                      << "output: " << cmd_in << '\n'
                      << "except: " << file_in << '\n'
                      << sep << std::endl;
            return 1;
        }
    }

    return 0;
}
