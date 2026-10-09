#include "tokenstream.hpp"
#include <stdexcept>

namespace parser {

TokenStream::TokenStream(std::vector<Token> tokens)
    : m_tokens(std::move(tokens)),
      m_eof_token{TokenType::EndOfFile, "", 0, 0} {}

const Token& TokenStream::peek() const {
    return peek_ahead(0);
}

const Token& TokenStream::peek_ahead(size_t offset) const {
    if (m_index + offset >= m_tokens.size()) {
        return m_eof_token;
    }
    return m_tokens[m_index + offset];
}

const Token& TokenStream::consume() {
    if (!at_end()) {
        return m_tokens[m_index++];
    }
    return m_eof_token;
}

bool TokenStream::match(TokenType type) {
    if (peek().type == type) {
        consume();
        return true;
    }
    return false;
}

const Token& TokenStream::expect(TokenType type, std::string_view error_msg) {
    if (peek().type == type) {
        return consume();
    }
    throw std::runtime_error(std::string(error_msg));
}

bool TokenStream::at_end() const {
    return m_index >= m_tokens.size() || m_tokens[m_index].type == TokenType::EndOfFile;
}

} // namespace parser