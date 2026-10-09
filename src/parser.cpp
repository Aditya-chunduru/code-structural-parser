#include "parser.hpp"
#include <stdexcept>

namespace parser {

Parser::Parser(TokenStream stream) : m_stream(std::move(stream)) {}

std::shared_ptr<ASTNode> Parser::parse_translation_unit() {
    auto root = std::make_shared<ASTNode>(ASTNodeType::TranslationUnit);

    while (!m_stream.at_end()) {
        if (auto decl = parse_declaration()) {
            root->add_child(std::move(decl));
        } else {
            // Advance if we hit unsupported syntax or trailing tokens
            m_stream.consume();
        }
    }

    return root;
}

std::shared_ptr<ASTNode> Parser::parse_declaration() {
    if (m_stream.peek().type == TokenType::KwNamespace) {
        return parse_namespace();
    }
    if (m_stream.peek().type == TokenType::KwClass || 
        m_stream.peek().type == TokenType::KwStruct) {
        return parse_class_or_struct();
    }
    return nullptr;
}

// Parses: namespace <Identifier> { ... }
std::shared_ptr<NamespaceDeclNode> Parser::parse_namespace() {
    m_stream.expect(TokenType::KwNamespace, "Expected 'namespace'");
    
    auto name_token = m_stream.expect(TokenType::Identifier, "Expected namespace name");
    auto node = std::make_shared<NamespaceDeclNode>(std::string(name_token.lexeme));

    m_stream.expect(TokenType::LeftBrace, "Expected '{' after namespace name");

    // Parse nested contents inside namespace
    while (!m_stream.at_end() && m_stream.peek().type != TokenType::RightBrace) {
        if (auto child = parse_declaration()) {
            node->add_child(std::move(child));
        } else {
            m_stream.consume();
        }
    }

    m_stream.expect(TokenType::RightBrace, "Expected '}' closing namespace");
    return node;
}

// Parses: class/struct <Identifier> { ... };
std::shared_ptr<ClassDeclNode> Parser::parse_class_or_struct() {
    bool is_struct = (m_stream.peek().type == TokenType::KwStruct);
    m_stream.consume(); // Consume 'class' or 'struct'

    auto name_token = m_stream.expect(TokenType::Identifier, "Expected class/struct name");
    auto node = std::make_shared<ClassDeclNode>(std::string(name_token.lexeme), is_struct);

    m_stream.expect(TokenType::LeftBrace, "Expected '{' in class declaration");

    // Skip body content until closing brace
    while (!m_stream.at_end() && m_stream.peek().type != TokenType::RightBrace) {
        m_stream.consume();
    }

    m_stream.expect(TokenType::RightBrace, "Expected '}' closing class declaration");
    
    // Classes/structs in C++ require a trailing semicolon
    m_stream.match(TokenType::Semicolon);

    return node;
}

} // namespace parser