#pragma once

#include <string>
#include <vector>
#include <memory>

namespace parser {

enum class ASTNodeType {
    TranslationUnit, // Root node representing the entire file
    NamespaceDecl,   // namespace Foo { ... }
    ClassDecl,       // class Bar { ... }
    StructDecl,      // struct Baz { ... }
    FunctionDecl,    // void do_work()
    FieldDecl        // Member variables
};

class ASTNode {
public:
    explicit ASTNode(ASTNodeType type) : m_type(type) {}
    virtual ~ASTNode() = default;

    [[nodiscard]] ASTNodeType type() const { return m_type; }

    // Parent/child relationship management
    void add_child(std::shared_ptr<ASTNode> child) {
        m_children.push_back(std::move(child));
    }

    [[nodiscard]] const std::vector<std::shared_ptr<ASTNode>>& children() const {
        return m_children;
    }

private:
    ASTNodeType m_type;
    std::vector<std::shared_ptr<ASTNode>> m_children;
};

// Represents C++ namespace declarations
class NamespaceDeclNode : public ASTNode {
public:
    explicit NamespaceDeclNode(std::string name)
        : ASTNode(ASTNodeType::NamespaceDecl), m_name(std::move(name)) {}

    [[nodiscard]] const std::string& name() const { return m_name; }

private:
    std::string m_name;
};

// Represents C++ class and struct declarations
class ClassDeclNode : public ASTNode {
public:
    ClassDeclNode(std::string name, bool is_struct)
        : ASTNode(is_struct ? ASTNodeType::StructDecl : ASTNodeType::ClassDecl),
          m_name(std::move(name)),
          m_is_struct(is_struct) {}

    [[nodiscard]] const std::string& name() const { return m_name; }
    [[nodiscard]] bool is_struct() const { return m_is_struct; }

private:
    std::string m_name;
    bool m_is_struct;
};

// Represents function declarations
class FunctionDeclNode : public ASTNode {
public:
    FunctionDeclNode(std::string return_type, std::string name)
        : ASTNode(ASTNodeType::FunctionDecl),
          m_return_type(std::move(return_type)),
          m_name(std::move(name)) {}

    [[nodiscard]] const std::string& return_type() const { return m_return_type; }
    [[nodiscard]] const std::string& name() const { return m_name; }

private:
    std::string m_return_type;
    std::string m_name;
};

} // namespace parser