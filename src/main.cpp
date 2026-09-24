#include "parser/parser.hpp"
#include <iostream>

int main() {
    constexpr std::string_view sample_code = R"(
namespace core {
    class Engine {
    public:
        void start();
    };
}
)";

    parser::CodeParser code_parser(sample_code);
    code_parser.parse();

    return 0;
}