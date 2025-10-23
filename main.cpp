#include <fstream>
#include <generator.hpp>
#include <iostream>

int main(int argc, const char* argv[]) {
    std::ifstream file(argv[1]);
    Suisya::generate(file, std::cout, [](auto) {});
}
