cmake_minimum_required(VERSION 3.20)
project("glist")

option(ENABLE_TESTS "Build tests and run them with CTest." OFF)

file(GLOB_RECURSE SRC_FILES source/*.c)

add_library(${PROJECT_NAME} STATIC ${SRC_FILES})

target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if (ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        gcov
    )
    target_compile_options(${PROJECT_NAME} PRIVATE --coverage -g)
endif()
