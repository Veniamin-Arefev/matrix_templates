cmake_minimum_required(VERSION 3.22)
project(matrix_templates)

set(CMAKE_CXX_STANDARD 20)

include_directories(source)
add_subdirectory(source)
add_subdirectory(lib)

set(SOURCE_FILES main.cpp)
add_executable(Matrix_templates_run ${SOURCE_FILES})
target_link_libraries(Matrix_templates_run Matrix_templates_lib)


