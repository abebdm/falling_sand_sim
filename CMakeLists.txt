cmake_minimum_required(VERSION 3.10)

# Define the project name
project(FallingSandSim LANGUAGES CXX)

# --- Configuration ---
# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable common warnings for robust code (equivalent to -Wall -Wextra -Wpedantic)
if (CMAKE_COMPILER_IS_GNUORCLANG)
    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()

# --- Source and Target Definition ---

# 1. Gather all source files from the 'src' directory
add_executable(sand_sim WIN32
    src/main.cpp
    src/particles.cpp
    src/physics.cpp
    src/renderer.cpp
    src/world.cpp
)

# 3. Add the 'include' directory so the compiler can find 'World.h' and 'Particles.h'
target_include_directories(sand_sim PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

# 4. (Optional) Set the output directory to 'bin' for cleaner structure, similar to the Makefile
set_target_properties(sand_sim PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin"
)

# --- External Libraries ---
# Find and link SDL2
find_package(SDL2 REQUIRED)
target_link_libraries(sand_sim PRIVATE SDL2::SDL2main SDL2::SDL2)