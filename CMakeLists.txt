cmake_minimum_required(VERSION 3.14)
project(caissaflow)

# C++ Standard Configuration
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dependencies (GoogleTest)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
# Prevent overriding parent project compiler settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Magic Bitboards Generation (Pre-build step)
add_executable(magic_gen src/magic_generator.cpp)

# Define the output file path
set(MAGIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/src/magic_data.h")

# Create a custom command to run the generator
# This runs ONLY if magic_gen changes or the header doesn't exist
add_custom_command(
    OUTPUT ${MAGIC_HEADER}
    COMMAND magic_gen > ${MAGIC_HEADER}
    DEPENDS magic_gen
    COMMENT "Generating Magic Bitboards header (magic_data.h)..."
)

# C. Create a custom target to enforce the dependency
# This acts as a bridge between the file generation and the library
add_custom_target(generate_magics_target DEPENDS ${MAGIC_HEADER})

# -------------------------------------------------------------
# Chess Engine Library (The Core)
# -------------------------------------------------------------
add_library(chess_core 
    src/attacks.cpp
    src/bitboard.cpp
    src/board.cpp
)

# IMPORTANT: Explicitly tell CMake that chess_core depends on the generation step.
# This ensures magics_generated.hpp is created BEFORE compiling attacks.cpp
add_dependencies(chess_core generate_magics_target)

# Include directories
target_include_directories(chess_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)


add_executable(caissa_engine
    src/main.cpp
)

# Link the executable with your core library
target_link_libraries(caissa_engine PRIVATE chess_core)

# -------------------------------------------------------------
# Unit Testing
# -------------------------------------------------------------
enable_testing()

add_executable(unit_tests 
tests/attacks/king_attacks.cpp
tests/attacks/knight_attacks.cpp
tests/attacks/pawn_attacks.cpp
tests/attacks/rook_attacks.cpp
)

# Link against the core library and GTest
target_link_libraries(unit_tests PRIVATE chess_core GTest::gtest_main)

# Auto-discover tests
include(GoogleTest)
gtest_discover_tests(unit_tests)
