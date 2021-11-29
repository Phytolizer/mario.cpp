#include "util/RegexMatch.hpp"
#include "pcre2.h"

RegexMatch::RegexMatch(std::string_view text, pcre2_code* code, pcre2_match_data* match_data, uint32_t index)
    : m_text(text), m_code(code), m_match_data(match_data), m_index(index)
{
}

std::string_view RegexMatch::getText()
{
    PCRE2_SIZE start = getStart();
    PCRE2_SIZE end = getEnd();
    return m_text.substr(start, end - start);
}

PCRE2_SIZE RegexMatch::getStart()
{
    return pcre2_get_ovector_pointer(m_match_data)[m_index * 2];
}

PCRE2_SIZE RegexMatch::getEnd()
{
    return pcre2_get_ovector_pointer(m_match_data)[m_index * 2 + 1];
}
