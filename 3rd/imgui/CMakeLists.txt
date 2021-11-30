cmake_minimum_required(VERSION 3.12...3.22)

project(
    "imgui"
    LANGUAGES "CXX"
    VERSION "1.85"
    DESCRIPTION "Immediate Mode GUI"
    HOMEPAGE_URL "https://github.com/ocornut/imgui"
)

add_library(
    "imgui"
    "imgui.cpp"
    "imgui_demo.cpp"
    "imgui_draw.cpp"
    "imgui_impl_glfw.cpp"
    "imgui_impl_opengl3.cpp"
    "imgui_tables.cpp"
    "imgui_widgets.cpp"
)
target_include_directories(
    "imgui"
    PUBLIC "${PROJECT_SOURCE_DIR}"
)
target_link_libraries(
    "imgui"
    PUBLIC "glfw"
)
