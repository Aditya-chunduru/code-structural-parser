#pragma once

#include <string_view>

namespace parser {

class CodeParser {
public:
    explicit CodeParser(std::string_view source);
    void parse();

private:
    std::string_view m_source;
};

} // namespace parser