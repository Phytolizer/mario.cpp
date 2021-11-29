#pragma once

#define PCRE2_CODE_UNIT_WIDTH 8
#define PCRE2_STATIC
#include <pcre2.h>
#include <string_view>

class RegexMatch
{
    std::string_view m_text;
    pcre2_code* m_code;
    pcre2_match_data* m_match_data;
    uint32_t m_index;

    RegexMatch(std::string_view text, pcre2_code* code, pcre2_match_data* match_data, uint32_t index);
    friend class RegexMatchData;

  public:
    std::string_view getText();
    PCRE2_SIZE getStart();
    PCRE2_SIZE getEnd();
};
