cmake_minimum_required(VERSION 3.12...3.22)

project(
    "physics.cpp"
    LANGUAGES "CXX"
    VERSION "0.1.0"
    DESCRIPTION "A physics engine in C++"
    HOMEPAGE_URL "https://github.com/Phytolizer/physics.cpp"
)

include(FetchContent)

FetchContent_Declare(
    "SDL"
    GIT_REPOSITORY "https://github.com/libsdl-org/SDL.git"
    GIT_TAG "release-2.0.16"
)
option(SDL_SHARED OFF)
FetchContent_MakeAvailable("SDL")

add_library(
    "physics"
    "src/physics/whatever.cpp"
)
target_link_libraries(
    "physics"
    PUBLIC "SDL"
)
