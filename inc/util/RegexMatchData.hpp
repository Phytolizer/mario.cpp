#pragma once

#include "util/RegexMatch.hpp"
#include <string_view>

#define PCRE2_CODE_UNIT_WIDTH 8
#define PCRE2_STATIC
#include <pcre2.h>

class RegexMatchData
{
    std::string_view m_text;
    pcre2_code* m_code;
    pcre2_match_data* m_matchData;
    RegexMatchData(std::string_view text, pcre2_code* code, pcre2_match_data* matchData);
    pcre2_match_data* raw();
    friend class Regex;

  public:
    RegexMatchData(RegexMatchData&& other) noexcept;
    RegexMatchData& operator=(RegexMatchData&& other) noexcept;
    ~RegexMatchData();
    RegexMatch get(uint32_t index);
    RegexMatch getNamed(std::string_view name);
    uint32_t getCount();
};
