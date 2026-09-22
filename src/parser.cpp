// Include our parser interface so main can instantiate CodeParser.
#include "parser/parser.hpp"

// Include standard I/O for printing startup status.
#include <iostream>

// 'main' is the required entry point function for every C++ program.
// It returns an integer status code to the Operating System (0 = success).
int main() {
    std::cout << "=== Code Structural Parser v0.1.0 ===\n";

    // Create a local string variable holding C++ code to test.
    std::string dummy_code = "int main() { return 0; }";

    // Instantiate an object of type CodeParser on the stack, passing dummy_code to constructor.
    parser::CodeParser parser(dummy_code);

    // Call the parse method on our object instance.
    parser.parse();

    // Returning 0 signals to PowerShell/Windows that the program executed without errors.
    return 0;
}