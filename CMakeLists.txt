cmake_minimum_required(VERSION 3.12...3.22)

project(
    "physics.cpp"
    LANGUAGES "CXX"
    VERSION "0.1.0"
    DESCRIPTION "A physics engine in C++"
    HOMEPAGE_URL "https://github.com/Phytolizer/physics.cpp"
)

set(CMAKE_CXX_STANDARD 20)

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

FetchContent_Declare(
    "fmt"
    GIT_REPOSITORY "https://github.com/fmtlib/fmt.git"
    GIT_TAG "8.0.1"
)
FetchContent_MakeAvailable("fmt")

FetchContent_Declare(
    "pcre"
    GIT_REPOSITORY "https://github.com/Phytolizer/pcre2.git"
    GIT_TAG "phyto-1.0"
)
FetchContent_MakeAvailable("pcre")

FetchContent_Declare(
    "glm"
    GIT_REPOSITORY "https://github.com/g-truc/glm.git"
    GIT_TAG "0.9.9.8"
)
FetchContent_MakeAvailable("glm")
find_package(protobuf CONFIG REQUIRED)

add_subdirectory("3rd/glad")
add_subdirectory("3rd/imgui")
add_subdirectory("3rd/stb")

list(
    APPEND
    CMAKE_CXX_FLAGS
    "-Wall"
)

add_library(
    "util"
    "src/util/Regex.cpp"
    "src/util/RegexMatch.cpp"
    "src/util/RegexMatchData.cpp"
    "src/util/Time.cpp"
)
target_include_directories("util" PUBLIC "${PROJECT_SOURCE_DIR}/inc")
target_link_libraries("util" PUBLIC "pcre2-8" "fmt")

add_library(
    "jade"
    "src/jade/Camera.cpp"
    "src/jade/Component.cpp"
    "src/jade/components/DependentSprite.cpp"
    "src/jade/components/DependentSpriteRenderer.cpp"
    "src/jade/components/FontRenderer.cpp"
    "src/jade/components/IndependentSprite.cpp"
    "src/jade/components/IndependentSpriteRenderer.cpp"
    "src/jade/components/Sprite.cpp"
    "src/jade/components/SpriteRenderer.cpp"
    "src/jade/components/SpriteSheet.cpp"
    "src/jade/GameObject.cpp"
    "src/jade/ImGuiLayer.cpp"
    "src/jade/KeyListener.cpp"
    "src/jade/LevelEditorScene.cpp"
    "src/jade/LevelScene.cpp"
    "src/jade/MouseListener.cpp"
    "src/jade/renderer/RenderBatch.cpp"
    "src/jade/renderer/Renderer.cpp"
    "src/jade/renderer/Shader.cpp"
    "src/jade/renderer/stb_image.cpp"
    "src/jade/renderer/Texture.cpp"
    "src/jade/Scene.cpp"
    "src/jade/Transform.cpp"
    "src/jade/Window.cpp"
)
target_include_directories("jade" PUBLIC "${PROJECT_SOURCE_DIR}/inc")
target_link_libraries(
    "jade"
    PUBLIC "fmt"
           "util"
           "glad"
           "glfw"
           "glm"
           "imgui"
           "protobuf::libprotobuf"
           "stb"
           "util"
)

add_library("physics" "src/physics/whatever.cpp")
target_include_directories("physics" PUBLIC "${PROJECT_SOURCE_DIR}/inc")

add_executable("mario" "src/mario/main.cpp")
target_link_libraries("mario" PRIVATE "jade" "nativefiledialog")
add_custom_command(
    TARGET "mario"
    POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_directory "${PROJECT_SOURCE_DIR}/res"
            "$<TARGET_FILE_DIR:mario>/res"
)
set_target_properties(
    "mario" PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
)
