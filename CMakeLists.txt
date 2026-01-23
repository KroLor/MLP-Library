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

add_executable(mlp_example example/example.cpp)
target_link_libraries(mlp_example PRIVATE mlp_lib)

add_custom_target(run_example
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/mlp_example
    DEPENDS mlp_example
    COMMENT "Running an example of using the library"
)
message(STATUS "Example mlp_example created")

option(BUILD_TEST "Build test application" ON)
if(BUILD_TEST)
    add_executable(mlp_test test/main.cpp)
    target_link_libraries(mlp_test PRIVATE mlp_lib)
    
    enable_testing()
    add_test(NAME mlp_test COMMAND mlp_test)
    
    add_custom_target(run_tests
        COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
        DEPENDS mlp_test
        COMMENT "Run all tests"
    )
    message(STATUS "Tests included")
else()
    message(STATUS "Tests are disabled")
endif()

if(MSVC)
    target_compile_options(mlp_lib PRIVATE /W4)
else()
    target_compile_options(mlp_lib PRIVATE -Wall -Wextra -pedantic)
endif()

message(STATUS "MLP-LIBRARY configured successfully!")