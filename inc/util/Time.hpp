#pragma once

#include <chrono>

struct Time
{
  private:
    using Millis = std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::milliseconds>;
    static Millis timeStarted;

  public:
    static float getTime();
};
