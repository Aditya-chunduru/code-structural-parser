# Require CMake version 3.20 or newer 
cmake_minimum_required(VERSION 3.20)


# Define the project name, version, and language (CXX stands for C++)
project(code_structural_parser VERSION 0.1.0 LANGUAGES CXX)

# Enforce C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Disable non-standard compiler extensions (keeps code portable across OS platforms)
set(CMAKE_CXX_EXTENSIONS OFF)

# Generate 'compile_commands.json' so IDEs (VS Code, CLion) get full autocomplete and diagnostics
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Define a variable containing all C++ source (.cpp) files needed for compilation
set(SOURCES
    src/main.cpp
    src/parser.cpp
)

# Tell CMake to compile those sources into an executable binary named 'code_structural_parser'
add_executable(${PROJECT_NAME} ${SOURCES})


# Specify where the compiler should look for header (.hpp) files when it sees #include
target_include_directories(${PROJECT_NAME} PRIVATE
${CMAKE_CURRENT_SOURCE_DIR}/include)

# Turn on strict compiler warnings to treat warnings as build errors (catches bugs early)
if(MSVC)
    # Flags for Microsoft Visual C++ compiler
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
    # Flags for GCC / Clang compilers
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()