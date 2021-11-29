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
    "glfw"
    GIT_REPOSITORY "https://github.com/glfw/glfw"
    GIT_TAG "3.3.5"
)
FetchContent_MakeAvailable("glfw")

FetchContent_Declare(
    "nativefiledialog"
    GIT_REPOSITORY "https://github.com/Phytolizer/nativefiledialog.git"
    GIT_TAG "master"
)
FetchContent_MakeAvailable("nativefiledialog")

add_subdirectory("3rd/glad")
add_subdirectory("3rd/stb")

add_library(
    "jade"
    "src/jade/KeyListener.cpp"
    "src/jade/MouseListener.cpp"
    "src/jade/Window.cpp"
)
target_include_directories(
    "jade"
    PUBLIC "${PROJECT_SOURCE_DIR}/inc"
)
target_link_libraries(
    "jade"
    PUBLIC "glfw" "glad"
)

add_library(
    "physics"
    "src/physics/whatever.cpp"
)
target_include_directories(
    "physics"
    PUBLIC "${PROJECT_SOURCE_DIR}/inc"
)

add_executable(
    "mario"
    "src/mario/main.cpp"
)
target_link_libraries(
    "mario"
    PRIVATE "nativefiledialog" "jade"
)
