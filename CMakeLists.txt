cmake_minimum_required(VERSION 3.21)
project(ProjectPhoenix VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Fetch SFML
include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1
    GIT_SHALLOW ON
)
FetchContent_MakeAvailable(SFML)

# Fetch ImGui
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.89.9
    GIT_SHALLOW ON
)
FetchContent_MakeAvailable(imgui)

# Fetch ImGui-SFML (needs IMGUI_DIR to find imgui sources)
set(IMGUI_DIR ${imgui_SOURCE_DIR})
set(IMGUI_SFML_FIND_SFML OFF)
set(IMGUI_SFML_IMGUI_DEMO ON CACHE BOOL "" FORCE)
FetchContent_Declare(
    imgui-sfml
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
    GIT_TAG v2.6
    GIT_SHALLOW ON
)
FetchContent_MakeAvailable(imgui-sfml)

# Collect engine source files
file(GLOB_RECURSE ENGINE_SOURCES "Engine/src/*.cpp")

# Create engine static library
add_library(PhoenixEngine STATIC ${ENGINE_SOURCES})

target_include_directories(PhoenixEngine PUBLIC
    ${CMAKE_SOURCE_DIR}/Engine/include
)

target_link_libraries(PhoenixEngine PUBLIC
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
    ImGui-SFML::ImGui-SFML
)

# Collect game source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

# Link engine (transitively provides SFML)
target_link_libraries(${PROJECT_NAME} PRIVATE
    PhoenixEngine
)

# Platform-specific settings
if(WIN32)
    # Copy SFML DLLs to output directory on Windows
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:sfml-graphics>
        $<TARGET_FILE:sfml-window>
        $<TARGET_FILE:sfml-system>
        $<TARGET_FILE:sfml-audio>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )

    # Hide console window for release builds on Windows
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
    endif()
elseif(APPLE)
    # macOS-specific settings
    set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE FALSE
    )

    # Set RPATH for macOS
    set_target_properties(${PROJECT_NAME} PROPERTIES
        BUILD_WITH_INSTALL_RPATH TRUE
        INSTALL_RPATH "@executable_path/../lib"
    )
endif()

# Compiler warnings
if(MSVC)
    target_compile_options(PhoenixEngine PRIVATE /W4)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(PhoenixEngine PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()
