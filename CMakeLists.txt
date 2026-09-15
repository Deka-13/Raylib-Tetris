cmake_minimum_required(VERSION 3.12)
project(tetris LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Raylib library (-lraylib) and header (<raylib.h>)
find_library(RAYLIB_LIBRARY NAMES raylib REQUIRED)
find_path(RAYLIB_INCLUDE_DIR NAMES raylib.h REQUIRED)

# Executable target and source files
add_executable(tetris
    main.cpp
    canvas.cpp
)

target_compile_options(tetris PRIVATE -Wall -Wextra -g)

# Include Raylib header path and link the library binary
target_include_directories(tetris PRIVATE ${RAYLIB_INCLUDE_DIR})
target_link_libraries(tetris PRIVATE ${RAYLIB_LIBRARY})

# Create 'make run' target
add_custom_target(run
    COMMAND tetris
    DEPENDS tetris
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Building and running the game..."
)
