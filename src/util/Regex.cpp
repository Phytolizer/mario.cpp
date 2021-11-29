#include "util/Regex.hpp"
#include "pcre2.h"
#include <fmt/format.h>
#include <stdexcept>

Regex::Regex(std::string_view pattern) : m_code(nullptr)
{
    int errorCode;
    PCRE2_SIZE errorOffset;
    m_code = pcre2_compile(reinterpret_cast<PCRE2_SPTR>(pattern.data()), pattern.size(), PCRE2_MULTILINE, &errorCode,
                           &errorOffset, nullptr);
    if (m_code == nullptr)
    {
        constexpr size_t buflen = 120;
        char buffer[buflen];
        pcre2_get_error_message(errorCode, reinterpret_cast<PCRE2_UCHAR*>(buffer), buflen);
        throw std::runtime_error{fmt::format("Error: Could not compile regex: '{}': {}", pattern, buffer)};
    }
}

Regex::~Regex()
{
    pcre2_code_free(m_code);
}

std::vector<RegexMatchData> Regex::findAll(std::string_view text)
{
    std::vector<RegexMatchData> results;
    size_t searchStart = 0;
    while (searchStart < text.size())
    {
        pcre2_match_data* matchData = pcre2_match_data_create_from_pattern(m_code, nullptr);
        int errorCode = pcre2_match(m_code, reinterpret_cast<PCRE2_SPTR>(text.data()), text.size(), searchStart, 0,
                                    matchData, nullptr);
        if (errorCode == PCRE2_ERROR_NOMATCH)
        {
            break;
        }
        if (errorCode < 0)
        {
            pcre2_match_data_free(matchData);
            char buffer[120];
            pcre2_get_error_message(errorCode, reinterpret_cast<PCRE2_UCHAR*>(buffer), 120);
            std::string message = fmt::format("Error: Could not find matches: {}", buffer);
            throw std::runtime_error{message};
        }
        searchStart = pcre2_get_ovector_pointer(matchData)[1];
        results.emplace_back(RegexMatchData{text, m_code, matchData});
    }
    return results;
}

std::vector<std::string> Regex::split(std::string_view text)
{
    pcre2_match_data* rawMatchData = pcre2_match_data_create_from_pattern(m_code, nullptr);
    RegexMatchData matchData{text, m_code, rawMatchData};
    int returnCode =
        pcre2_match(m_code, reinterpret_cast<PCRE2_SPTR>(text.data()), text.size(), 0, 0, matchData.raw(), nullptr);
    if (returnCode < 0)
    {
        char buffer[120];
        pcre2_get_error_message(returnCode, reinterpret_cast<PCRE2_UCHAR*>(buffer), 120);
        throw std::runtime_error{fmt::format("Error: Could not match regex: {}", buffer)};
    }
    uint32_t matchCount = matchData.getCount();
    if (matchCount == 0)
    {
        return {std::string{text}};
    }
    std::vector<std::string> results;
    results.reserve(matchCount + 1);
    PCRE2_SIZE prevEnd = 0;
    for (uint32_t i = 0; i < matchCount; ++i)
    {
        PCRE2_SIZE start = matchData.get(i).getStart();
        results.emplace_back(text.substr(prevEnd, start - prevEnd));
        prevEnd = matchData.get(i).getEnd();
    }
    results.emplace_back(text.substr(prevEnd));
    return results;
}
