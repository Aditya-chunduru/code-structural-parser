#pragma once

#include <cstdint>
#include <string_view>

namespace parser {

enum class TokenType : uint16_t {
    // Special
    EndOfFile,
    Unknown,

    // Structural Keywords
    KwClass,
    KwStruct,
    KwEnum,
    KwNamespace,
    KwPublic,
    KwProtected,
    KwPrivate,
    KwVirtual,
    KwOverride,
    KwFinal,
    KwConst,
    KwConstexpr,
    KwTemplate,
    KwTypename,
    KwAuto,
    KwVoid,
    KwUsing,
    KwTypedef,
    KwFriend,
    KwStatic,
    KwInline,

    // Identifiers & Literals
    Identifier,
    IntegerLiteral,
    FloatLiteral,
    StringLiteral,
    CharLiteral,

    // Structural Delimiters & Operators
    LeftParen,        // (
    RightParen,       // )
    LeftBrace,        // {
    RightBrace,       // }
    LeftBracket,      // [
    RightBracket,     // ]
    Semicolon,        // ;
    Colon,            // :
    ScopeResolution,  // ::
    Comma,            // ,
    Dot,              // .
    Arrow,            // ->
    Assign,           // =
    Equal,            // ==
    NotEqual,         // !=
    LessThan,         // <  (also template start)
    GreaterThan,      // >  (also template end)

    // Comments (useful for doc-comment extraction or stripping)
    LineComment,
    BlockComment
};

struct Token {
    TokenType type{TokenType::Unknown};
    std::string_view lexeme{};
    std::size_t line{1};
    std::size_t column{1};
};

constexpr std::string_view to_string(TokenType type) noexcept {
    switch (type) {
        case TokenType::EndOfFile:        return "EndOfFile";
        case TokenType::Unknown:          return "Unknown";
        case TokenType::KwClass:          return "KwClass";
        case TokenType::KwStruct:         return "KwStruct";
        case TokenType::KwEnum:           return "KwEnum";
        case TokenType::KwNamespace:      return "KwNamespace";
        case TokenType::KwPublic:         return "KwPublic";
        case TokenType::KwProtected:      return "KwProtected";
        case TokenType::KwPrivate:        return "KwPrivate";
        case TokenType::KwVirtual:        return "KwVirtual";
        case TokenType::KwOverride:       return "KwOverride";
        case TokenType::KwFinal:          return "KwFinal";
        case TokenType::KwConst:          return "KwConst";
        case TokenType::KwConstexpr:      return "KwConstexpr";
        case TokenType::KwTemplate:       return "KwTemplate";
        case TokenType::KwTypename:       return "KwTypename";
        case TokenType::KwAuto:           return "KwAuto";
        case TokenType::KwVoid:           return "KwVoid";
        case TokenType::KwUsing:          return "KwUsing";
        case TokenType::KwTypedef:        return "KwTypedef";
        case TokenType::KwFriend:         return "KwFriend";
        case TokenType::KwStatic:         return "KwStatic";
        case TokenType::KwInline:         return "KwInline";
        case TokenType::Identifier:       return "Identifier";
        case TokenType::IntegerLiteral:   return "IntegerLiteral";
        case TokenType::FloatLiteral:     return "FloatLiteral";
        case TokenType::StringLiteral:    return "StringLiteral";
        case TokenType::CharLiteral:      return "CharLiteral";
        case TokenType::LeftParen:        return "LeftParen";
        case TokenType::RightParen:       return "RightParen";
        case TokenType::LeftBrace:        return "LeftBrace";
        case TokenType::RightBrace:       return "RightBrace";
        case TokenType::LeftBracket:      return "LeftBracket";
        case TokenType::RightBracket:     return "RightBracket";
        case TokenType::Semicolon:        return "Semicolon";
        case TokenType::Colon:            return "Colon";
        case TokenType::ScopeResolution:  return "ScopeResolution";
        case TokenType::Comma:            return "Comma";
        case TokenType::Dot:              return "Dot";
        case TokenType::Arrow:            return "Arrow";
        case TokenType::Assign:           return "Assign";
        case TokenType::Equal:            return "Equal";
        case TokenType::NotEqual:         return "NotEqual";
        case TokenType::LessThan:         return "LessThan";
        case TokenType::GreaterThan:      return "GreaterThan";
        case TokenType::LineComment:      return "LineComment";
        case TokenType::BlockComment:     return "BlockComment";
    }
    return "Unknown";
}

} // namespace parser