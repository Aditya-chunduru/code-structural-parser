// '#pragma once' is a header guard. It prevents the compiler from loading 
// this header file more than once per build, avoiding duplicate definition errors.
#pragma once

// <string> provides std::string for dynamic text strings that own their memory.
#include <string>

// <string_view> provides std::string_view for lightweight, read-only references 
// to string data without making expensive copies.
#include <string_view>

// <vector> provides std::vector, C++'s dynamic resizing array (like an ArrayList).
#include <vector>

// Namespaces organize code into distinct scopes to prevent function/class name collisions.
namespace parser {

// A 'struct' is a simple data container. In C++, members of a struct are public by default.
struct Token {
    std::string type;   // Category of token (e.g., "KEYWORD", "IDENTIFIER", "SYMBOL")
    std::string value;  // The actual text snippet (e.g., "int", "main", "{")
    size_t line;        // Line number in source code (size_t is an unsigned integer for sizes)
};

// A 'class' encapsulates data and methods. In C++, class members are private by default.
class CodeParser {
public:
    // 'explicit' prevents implicit type conversions when passing arguments to this constructor.
    // We pass std::string_view by value because it is cheap (just a pointer + length).
    explicit CodeParser(std::string_view source);

    // Declaration of the parsing routine. Logic will live in parser.cpp.
    void parse();
    
private:
    // 'm_' prefix is a standard naming convention for private Member variables.
    std::string_view m_source;   // Holds a view of the source code string being parsed
    std::vector<Token> m_tokens; // Dynamic vector that will store generated tokens
};

} // namespace parser