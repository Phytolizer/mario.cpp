#include "util/Time.hpp"
#include <chrono>
#include <ratio>

Time::Millis Time::timeStarted =
    std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now());

float Time::getTime()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() -
                                                                 timeStarted)
               .count() /
           1000.0F;
}
