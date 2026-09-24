#pragma once

#include "parser/Token.hpp"
#include <string_view>
#include <vector>
#include <unordered_map>

namespace parser {

class Lexer {
public:
    explicit Lexer(std::string_view source) noexcept
        : m_source(source) {}

    /// Scans and returns the next token in the stream.
    Token next_token() noexcept;

    /// Helper utility to scan all remaining tokens into a vector.
    [[nodiscard]] std::vector<Token> tokenize_all() noexcept;

    /// Resets lexer state to re-scan from the beginning.
    void reset() noexcept {
        m_cursor = 0;
        m_line = 1;
        m_column = 1;
    }

private:
    std::string_view m_source;
    std::size_t m_cursor{0};
    std::size_t m_line{1};
    std::size_t m_column{1};

    // --- Cursor Navigation Helpers ---
    [[nodiscard]] bool is_at_end() const noexcept {
        return m_cursor >= m_source.size();
    }

    [[nodiscard]] char peek(std::size_t offset = 0) const noexcept {
        if (m_cursor + offset >= m_source.size()) {
            return '\0';
        }
        return m_source[m_cursor + offset];
    }

    char advance() noexcept {
        if (is_at_end()) return '\0';
        char c = m_source[m_cursor++];
        if (c == '\n') {
            m_line++;
            m_column = 1;
        } else {
            m_column++;
        }
        return c;
    }

    bool match(char expected) noexcept {
        if (is_at_end() || m_source[m_cursor] != expected) {
            return false;
        }
        advance();
        return true;
    }

    // --- Scanning Subroutines ---
    void skip_whitespace() noexcept;
    Token scan_identifier_or_keyword(std::size_t start_line, std::size_t start_col) noexcept;
    Token scan_number(std::size_t start_line, std::size_t start_col) noexcept;
    Token scan_string_literal(std::size_t start_line, std::size_t start_col) noexcept;
    Token scan_char_literal(std::size_t start_line, std::size_t start_col) noexcept;
    Token scan_line_comment(std::size_t start_line, std::size_t start_col) noexcept;
    Token scan_block_comment(std::size_t start_line, std::size_t start_col) noexcept;

    // --- Keyword Lookup ---
    [[nodiscard]] static TokenType lookup_keyword(std::string_view lexeme) noexcept;
};

} // namespace parser