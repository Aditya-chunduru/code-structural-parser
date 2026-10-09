#pragma once

#include "token.hpp"
#include <vector>
#include <cstddef>
#include <optional>

namespace parser {

class TokenStream {
public:
    explicit TokenStream(std::vector<Token> tokens);

    // Look at the current token without advancing
    [[nodiscard]] const Token& peek() const;

    // Look ahead N tokens without advancing (default offset = 1)
    [[nodiscard]] const Token& peek_ahead(size_t offset) const;

    // Advance the cursor and return the consumed token
    const Token& consume();

    // Check if current token matches expected type; if so, consume and return true
    bool match(TokenType type);

    // Consume current token if type matches; throw/error if it doesn't
    const Token& expect(TokenType type, std::string_view error_msg);

    // Helper checks
    [[nodiscard]] bool at_end() const;
    [[nodiscard]] size_t position() const { return m_index; }

private:
    std::vector<Token> m_tokens;
    size_t m_index{0};
    Token m_eof_token; // Fallback token when reaching end of stream
};

} // namespace parser