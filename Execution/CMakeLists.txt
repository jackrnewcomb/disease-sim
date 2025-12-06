cmake_minimum_required(VERSION 3.12)
project(Execution LANGUAGES CXX)

# Collect main source file
file(GLOB_RECURSE SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
)

# Create executable
add_executable(execute ${SOURCES})

# Link to your libraries
target_link_libraries(execute PRIVATE environment agent visual)

# Set C++ standard
target_compile_features(execute PUBLIC cxx_std_17)

# Include directories
target_include_directories(execute PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# Make sure your executable depends on all DLL targets
set(SFML_BIN "${CMAKE_BINARY_DIR}/SFML/lib/$<CONFIG>")

# Ensure the output folder exists
add_custom_command(TARGET execute POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:execute>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:visual> $<TARGET_FILE_DIR:execute>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:environment> $<TARGET_FILE_DIR:execute>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:agent> $<TARGET_FILE_DIR:execute>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${SFML_BIN}/sfml-graphics$<$<CONFIG:Debug>:-d>-2.dll" $<TARGET_FILE_DIR:execute>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${SFML_BIN}/sfml-window$<$<CONFIG:Debug>:-d>-2.dll"  $<TARGET_FILE_DIR:execute>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${SFML_BIN}/sfml-system$<$<CONFIG:Debug>:-d>-2.dll"  $<TARGET_FILE_DIR:execute>
)

# Copy graphics/ into the build (binary) directory
file(COPY ${PROJECT_SOURCE_DIR}/graphics DESTINATION ${CMAKE_BINARY_DIR}/Execution)
