cmake_minimum_required(VERSION 3.12...3.22)

project(
    "stb"
    DESCRIPTION "Single-file libraries for C/C++"
    HOMEPAGE_URL "https://github.com/nothings/stb"
)

add_library(
    "stb"
    INTERFACE
)
target_include_directories(
    "stb"
    INTERFACE
    "${PROJECT_SOURCE_DIR}"
)
