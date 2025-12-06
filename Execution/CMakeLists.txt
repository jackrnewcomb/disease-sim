cmake_minimum_required(VERSION 3.12)
project(Execution LANGUAGES CXX)

# Collect source and header files
file(GLOB_RECURSE SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
)

# Create a library from these files
add_executable(execute ${SOURCES})

target_link_libraries(execute PRIVATE environment agent)

# Set C++ standard (optional)
target_compile_features(execute PUBLIC cxx_std_17)

# Expose include directory to whoever links against this library
target_include_directories(execute PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
