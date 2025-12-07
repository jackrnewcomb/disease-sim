cmake_minimum_required(VERSION 3.12)
project(Environment LANGUAGES CXX)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)


# Collect source and header files
file(GLOB_RECURSE SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
)

# Create a library from these files
add_library(environment ${SOURCES})
include_directories(${PROJECT_SOURCE_DIR}/../SFML/include)
link_directories(${PROJECT_SOURCE_DIR}/../SFML/lib)

target_link_libraries(environment PRIVATE agent sfml-graphics)

# Set C++ standard (optional)
target_compile_features(environment PUBLIC cxx_std_17)

# Expose include directory to whoever links against this library
target_include_directories(environment PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
