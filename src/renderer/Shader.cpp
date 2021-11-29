#include "renderer/Shader.hpp"
#include "fmt/core.h"
#include <fstream>
#include <iostream>
#include <util/Regex.hpp>

Shader::Shader(std::string_view filePath) : m_filePath(filePath)
{
    std::ifstream shaderFile{std::string{filePath.begin(), filePath.end()}};
    if (!shaderFile)
    {
        throw std::runtime_error{fmt::format("Error: Could not open file for shader: '{}'", filePath)};
    }
    std::string source{std::istreambuf_iterator<char>{shaderFile}, std::istreambuf_iterator<char>{}};
    Regex typeRegex{R"(#type\s+(vertex|fragment))"};
    std::vector<RegexMatchData> matches = typeRegex.findAll(source);
    std::cout << "=============== MATCHES ================" << std::endl;
    for (size_t i = 0; i < matches.size(); i++)
    {
        auto& match = matches[i];
        std::cout << "========================================" << std::endl;
        std::cout << match.get(1).getStart() << std::endl;
        std::cout << match.get(1).getEnd() << std::endl;
        std::cout << match.get(1).getText() << std::endl;
        auto slice = [&]() {
            PCRE2_SIZE start = match.get(1).getEnd();
            PCRE2_SIZE end;
            if (i < matches.size() - 1)
            {
                end = matches[i + 1].get(0).getStart();
            }
            else
            {
                end = source.size();
            }
            return std::string{source.begin() + start, source.begin() + end};
        };
        if (match.get(1).getText() == "vertex")
        {
            m_vertexSource = slice();
        }
        else if (match.get(1).getText() == "fragment")
        {
            m_fragmentSource = slice();
        }
        else
        {
            std::string message = fmt::format("Error: Unknown shader type '{}'", match.get(1).getText());
            throw std::runtime_error{message};
        }
    }

    std::cout << "=============== VERTEX ================" << std::endl;
    std::cout << m_vertexSource << std::endl;
    std::cout << "=============== FRAGMENT ================" << std::endl;
    std::cout << m_fragmentSource << std::endl;
}
