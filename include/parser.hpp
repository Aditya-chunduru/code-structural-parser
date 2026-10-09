#pragma once

#include "tokenstream.hpp"
#include "astnode.hpp"
#include <memory>

namespace parser {

class Parser {
public:
    explicit Parser(TokenStream stream);

    // Main entry point: parses the entire stream into an AST root node
    [[nodiscard]] std::shared_ptr<ASTNode> parse_translation_unit();

private:
    TokenStream m_stream;

    // Parsing sub-routines (Recursive Descent Rules)
    std::shared_ptr<ASTNode> parse_declaration();
    std::shared_ptr<NamespaceDeclNode> parse_namespace();
    std::shared_ptr<ClassDeclNode> parse_class_or_struct();
};
} // namespace parser