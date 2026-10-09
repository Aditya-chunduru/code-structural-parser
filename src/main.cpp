#include "lexer.hpp"
#include "tokenstream.hpp"
#include "parser.hpp"
#include <iostream>
#include <string>

void print_ast(const std::shared_ptr<parser::ASTNode>& node, int indent = 0) {
    if (!node) return;

    std::string indent_str(indent * 2, ' ');

    switch (node->type()) {
        case parser::ASTNodeType::TranslationUnit:
            std::cout << indent_str << "[TranslationUnit]\n";
            break;
        case parser::ASTNodeType::NamespaceDecl: {
            auto ns = std::static_pointer_cast<parser::NamespaceDeclNode>(node);
            std::cout << indent_str << "└── NamespaceDecl: " << ns->name() << "\n";
            break;
        }
        case parser::ASTNodeType::ClassDecl:
        case parser::ASTNodeType::StructDecl: {
            auto cls = std::static_pointer_cast<parser::ClassDeclNode>(node);
            std::cout << indent_str << "└── " << (cls->is_struct() ? "StructDecl: " : "ClassDecl: ")
                      << cls->name() << "\n";
            break;
        }
        case parser::ASTNodeType::FunctionDecl: {
            auto fn = std::static_pointer_cast<parser::FunctionDeclNode>(node);
            std::cout << indent_str << "└── FunctionDecl: " << fn->return_type() 
                      << " " << fn->name() << "()\n";
            break;
        }
        default:
            std::cout << indent_str << "└── ASTNode\n";
            break;
    }

    for (const auto& child : node->children()) {
        print_ast(child, indent + 1);
    }
}

int main() {
    std::string sample_code = R"(
        namespace core {
            class Engine {
            };
            struct Config {
            };
        }
    )";

    parser::Lexer lexer(sample_code);
    auto tokens = lexer.tokenize_all();

    parser::TokenStream stream(std::move(tokens));
    parser::Parser parser_engine(std::move(stream));

    auto ast = parser_engine.parse_translation_unit();

    std::cout << "Successfully parsed code! Root child count: " 
              << ast->children().size() << std::endl;

    print_ast(ast);
    return 0;
}