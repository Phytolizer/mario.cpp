#include "util/RegexMatchData.hpp"
#include "pcre2.h"
#include <fmt/format.h>
#include <stdexcept>

RegexMatchData::RegexMatchData(std::string_view text, pcre2_code* code, pcre2_match_data* matchData)
    : m_text(text), m_code(code), m_matchData(matchData)
{
}

pcre2_match_data* RegexMatchData::raw()
{
    return m_matchData;
}

RegexMatchData::RegexMatchData(RegexMatchData&& other) noexcept
    : m_text(other.m_text), m_code(other.m_code), m_matchData(other.m_matchData)
{
    other.m_matchData = nullptr;
}

RegexMatchData& RegexMatchData::operator=(RegexMatchData&& other) noexcept
{
    if (&other != this)
    {
        m_text = other.m_text;
        m_code = other.m_code;
        m_matchData = other.m_matchData;
        other.m_matchData = nullptr;
    }
    return *this;
}

RegexMatchData::~RegexMatchData()
{
    pcre2_match_data_free(m_matchData);
}

RegexMatch RegexMatchData::get(uint32_t index)
{
    return RegexMatch{m_text, m_code, m_matchData, index};
}

RegexMatch RegexMatchData::getNamed(std::string_view name)
{
    int index = pcre2_substring_number_from_name(m_code, reinterpret_cast<PCRE2_SPTR>(name.data()));
    if (index == PCRE2_ERROR_NOSUBSTRING)
    {
        throw std::runtime_error{fmt::format("Error: Could not find named group '{}'", name)};
    }
    if (index == PCRE2_ERROR_NOUNIQUESUBSTRING)
    {
        throw std::runtime_error{fmt::format("Error: Named group '{}' is not unique", name)};
    }
    return get(index);
}

uint32_t RegexMatchData::getCount()
{
    return pcre2_get_ovector_count(m_matchData);
}
