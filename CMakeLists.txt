cmake_minimum_required(VERSION 4.1.0)
project(MLPLib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_library(mlp_lib SHARED src/MLP.cpp)
target_include_directories(mlp_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

option(BUILD_TEST "Build test application" ON)
if(BUILD_TEST)
    add_executable(mlp_test test/main.cpp)
    target_link_libraries(mlp_test PRIVATE mlp_lib)
    target_include_directories(mlp_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
endif()

add_executable(mlp_example example/minimal_example.cpp)
target_link_libraries(mlp_example PRIVATE mlp_lib)
target_include_directories(mlp_example PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

if(MSVC)
    target_compile_options(mlp_lib PRIVATE /W4)
else()
    target_compile_options(mlp_lib PRIVATE -Wall -Wextra -pedantic)
endif()

message(STATUS "MLP-LIBRARY configured successfully!")