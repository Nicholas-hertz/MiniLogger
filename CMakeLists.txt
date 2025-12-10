cmake_minimum_required(VERSION 3.16)
project(MiniLogger VERSION 1.0 LANGUAGES CXX)

# Set C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optional: set warnings
if(MSVC)
    set(WARNING_FLAGS /W4 /permissive-)
else()
    set(WARNING_FLAGS -Wall -Wextra -Wpedantic -Werror)
endif()

# ===============================
# MiniLogger Library
# ===============================
add_library(MiniLogger
    src/Logger.cpp
    src/FileSink.cpp
    src/Formatter.cpp
    src/ConsoleSink.cpp
)

target_include_directories(MiniLogger PUBLIC include)
target_compile_options(MiniLogger PRIVATE ${WARNING_FLAGS})

# ===============================
# Example Executable
# ===============================
add_executable(example examples/main.cpp)
target_link_libraries(example PRIVATE MiniLogger)
target_compile_options(example PRIVATE ${WARNING_FLAGS})
