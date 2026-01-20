cmake_minimum_required(VERSION 3.10)
project(Engine)

set(CMAKE_CXX_STANDARD 17)

# The Engine library
add_library(engine_lib STATIC
    src/Engine.cpp
    src/Entity.cpp
    src/Physics.cpp
    src/Input.cpp
    src/Collision.cpp
)

# This is the corrected include directory. It points to the parent "include" folder
# so that the compiler can resolve includes like <engine/Engine.h>
target_include_directories(engine_lib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Find SDL3 and link to it
find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
target_link_libraries(engine_lib PUBLIC SDL3::SDL3 SDL3_image::SDL3_image)
