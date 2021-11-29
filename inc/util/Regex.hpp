#pragma once

#include "util/RegexMatchData.hpp"
#include <string>
#include <string_view>
#include <vector>

#define PCRE2_CODE_UNIT_WIDTH 8
#define PCRE2_STATIC
#include <pcre2.h>

class Regex
{
    pcre2_code* m_code;

  public:
    explicit Regex(std::string_view pattern);
    ~Regex();
    std::vector<RegexMatchData> findAll(std::string_view text);
    std::vector<std::string> split(std::string_view text);
};
