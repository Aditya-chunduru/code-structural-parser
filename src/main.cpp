// Include our own matching header file so the compiler links declarations to definitions.
#include "parser/parser.hpp"

// <iostream> provides standard input/output stream capabilities (like printing to terminal).
#include <iostream>

namespace parser {

// Constructor definition.
// ': m_source(source)' is a "Member Initializer List". It directly assigns the 
// parameter 'source' to the member variable 'm_source' before the body runs.
CodeParser::CodeParser(std::string_view source) 
    : m_source(source) {}

// Implementation of the parse method declared in parser.hpp.
void CodeParser::parse() {
    // 'std::cout' streams text to standard output.
    // 'm_source.size()' returns the length of the string view in bytes.
    // '\n' creates a newline (faster than std::endl because it doesn't force a buffer flush).
    std::cout << "Initializing parser for " << m_source.size() << " bytes of source code...\n";
    
    // Lexical analysis logic will be added here next.
}

} // namespace parser