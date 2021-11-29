cmake_minimum_required(VERSION 3.12...3.22)

project(
    "glad"
    LANGUAGES "C"
    VERSION "0.1.34"
    DESCRIPTION "GL loader library"
    HOMEPAGE_URL "https://glad.dav1d.de/"
)

add_library(
    "glad"
    "src/glad.c"
)
target_include_directories(
    "glad"
    PUBLIC "${PROJECT_SOURCE_DIR}/include"
)
