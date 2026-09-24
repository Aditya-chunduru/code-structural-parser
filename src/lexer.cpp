#include "parser/Lexer.hpp"
#include <cctype>

namespace parser {

TokenType Lexer::lookup_keyword(std::string_view lexeme) noexcept {
    static const std::unordered_map<std::string_view, TokenType> keywords = {
        {"class", TokenType::KwClass},
        {"struct", TokenType::KwStruct},
        {"enum", TokenType::KwEnum},
        {"namespace", TokenType::KwNamespace},
        {"public", TokenType::KwPublic},
        {"protected", TokenType::KwProtected},
        {"private", TokenType::KwPrivate},
        {"virtual", TokenType::KwVirtual},
        {"override", TokenType::KwOverride},
        {"final", TokenType::KwFinal},
        {"const", TokenType::KwConst},
        {"constexpr", TokenType::KwConstexpr},
        {"template", TokenType::KwTemplate},
        {"typename", TokenType::KwTypename},
        {"auto", TokenType::KwAuto},
        {"void", TokenType::KwVoid},
        {"using", TokenType::KwUsing},
        {"typedef", TokenType::KwTypedef},
        {"friend", TokenType::KwFriend},
        {"static", TokenType::KwStatic},
        {"inline", TokenType::KwInline}
    };

    if (auto it = keywords.find(lexeme); it != keywords.end()) {
        return it->second;
    }
    return TokenType::Identifier;
}

void Lexer::skip_whitespace() noexcept {
    while (!is_at_end()) {
        char c = peek();
        if (c == ' ' || c == '\t' || c == '\r' || c == '\n') {
            advance();
        } else {
            break;
        }
    }
}

Token Lexer::scan_identifier_or_keyword(std::size_t start_line, std::size_t start_col) noexcept {
    std::size_t start_pos = m_cursor - 1;
    while (!is_at_end() && (std::isalnum(static_cast<unsigned char>(peek())) || peek() == '_')) {
        advance();
    }
    std::string_view lexeme = m_source.substr(start_pos, m_cursor - start_pos);
    TokenType type = lookup_keyword(lexeme);
    return Token{type, lexeme, start_line, start_col};
}

Token Lexer::scan_number(std::size_t start_line, std::size_t start_col) noexcept {
    std::size_t start_pos = m_cursor - 1;
    bool is_float = false;

    while (!is_at_end() && (std::isdigit(static_cast<unsigned char>(peek())) || peek() == '.')) {
        if (peek() == '.') {
            if (is_float) break; // Stop at second dot (e.g., member access or range)
            is_float = true;
        }
        advance();
    }

    std::string_view lexeme = m_source.substr(start_pos, m_cursor - start_pos);
    return Token{is_float ? TokenType::FloatLiteral : TokenType::IntegerLiteral, lexeme, start_line, start_col};
}

Token Lexer::scan_string_literal(std::size_t start_line, std::size_t start_col) noexcept {
    std::size_t start_pos = m_cursor - 1;
    while (!is_at_end()) {
        char c = advance();
        if (c == '\\') {
            if (!is_at_end()) advance(); // Skip escape character
        } else if (c == '"') {
            break;
        }
    }
    std::string_view lexeme = m_source.substr(start_pos, m_cursor - start_pos);
    return Token{TokenType::StringLiteral, lexeme, start_line, start_col};
}

Token Lexer::scan_char_literal(std::size_t start_line, std::size_t start_col) noexcept {
    std::size_t start_pos = m_cursor - 1;
    while (!is_at_end()) {
        char c = advance();
        if (c == '\\') {
            if (!is_at_end()) advance(); // Skip escape character
        } else if (c == '\'') {
            break;
        }
    }
    std::string_view lexeme = m_source.substr(start_pos, m_cursor - start_pos);
    return Token{TokenType::CharLiteral, lexeme, start_line, start_col};
}

Token Lexer::scan_line_comment(std::size_t start_line, std::size_t start_col) noexcept {
    std::size_t start_pos = m_cursor - 1;
    advance(); // Consume second '/'
    while (!is_at_end() && peek() != '\n') {
        advance();
    }
    std::string_view lexeme = m_source.substr(start_pos, m_cursor - start_pos);
    return Token{TokenType::LineComment, lexeme, start_line, start_col};
}

Token Lexer::scan_block_comment(std::size_t start_line, std::size_t start_col) noexcept {
    std::size_t start_pos = m_cursor - 1;
    advance(); // Consume '*'
    while (!is_at_end()) {
        if (peek() == '*' && peek(1) == '/') {
            advance(); // '*'
            advance(); // '/'
            break;
        }
        advance();
    }
    std::string_view lexeme = m_source.substr(start_pos, m_cursor - start_pos);
    return Token{TokenType::BlockComment, lexeme, start_line, start_col};
}

Token Lexer::next_token() noexcept {
    skip_whitespace();

    if (is_at_end()) {
        return Token{TokenType::EndOfFile, std::string_view{}, m_line, m_column};
    }

    std::size_t start_line = m_line;
    std::size_t start_col = m_column;
    std::size_t start_pos = m_cursor;

    char c = advance();

    if (std::isalpha(static_cast<unsigned char>(c)) || c == '_') {
        return scan_identifier_or_keyword(start_line, start_col);
    }

    if (std::isdigit(static_cast<unsigned char>(c))) {
        return scan_number(start_line, start_col);
    }

    switch (c) {
        case '"':
            return scan_string_literal(start_line, start_col);
        case '\'':
            return scan_char_literal(start_line, start_col);
        case '/':
            if (peek() == '/') return scan_line_comment(start_line, start_col);
            if (peek() == '*') return scan_block_comment(start_line, start_col);
            return Token{TokenType::Unknown, m_source.substr(start_pos, 1), start_line, start_col};
        case '(':
            return Token{TokenType::LeftParen, m_source.substr(start_pos, 1), start_line, start_col};
        case ')':
            return Token{TokenType::RightParen, m_source.substr(start_pos, 1), start_line, start_col};
        case '{':
            return Token{TokenType::LeftBrace, m_source.substr(start_pos, 1), start_line, start_col};
        case '}':
            return Token{TokenType::RightBrace, m_source.substr(start_pos, 1), start_line, start_col};
        case '[':
            return Token{TokenType::LeftBracket, m_source.substr(start_pos, 1), start_line, start_col};
        case ']':
            return Token{TokenType::RightBracket, m_source.substr(start_pos, 1), start_line, start_col};
        case ';':
            return Token{TokenType::Semicolon, m_source.substr(start_pos, 1), start_line, start_col};
        case ',':
            return Token{TokenType::Comma, m_source.substr(start_pos, 1), start_line, start_col};
        case '.':
            return Token{TokenType::Dot, m_source.substr(start_pos, 1), start_line, start_col};
        case ':':
            if (match(':')) {
                return Token{TokenType::ScopeResolution, m_source.substr(start_pos, 2), start_line, start_col};
            }
            return Token{TokenType::Colon, m_source.substr(start_pos, 1), start_line, start_col};
        case '-':
            if (match('>')) {
                return Token{TokenType::Arrow, m_source.substr(start_pos, 2), start_line, start_col};
            }
            return Token{TokenType::Unknown, m_source.substr(start_pos, 1), start_line, start_col};
        case '=':
            if (match('=')) {
                return Token{TokenType::Equal, m_source.substr(start_pos, 2), start_line, start_col};
            }
            return Token{TokenType::Assign, m_source.substr(start_pos, 1), start_line, start_col};
        case '!':
            if (match('=')) {
                return Token{TokenType::NotEqual, m_source.substr(start_pos, 2), start_line, start_col};
            }
            return Token{TokenType::Unknown, m_source.substr(start_pos, 1), start_line, start_col};
        case '<':
            return Token{TokenType::LessThan, m_source.substr(start_pos, 1), start_line, start_col};
        case '>':
            return Token{TokenType::GreaterThan, m_source.substr(start_pos, 1), start_line, start_col};
        default:
            return Token{TokenType::Unknown, m_source.substr(start_pos, 1), start_line, start_col};
    }
}

std::vector<Token> Lexer::tokenize_all() noexcept {
    std::vector<Token> tokens;
    while (true) {
        Token token = next_token();
        tokens.push_back(token);
        if (token.type == TokenType::EndOfFile) {
            break;
        }
    }
    return tokens;
}

} // namespace parser