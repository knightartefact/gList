cmake_minimum_required(VERSION 3.20)
project("gencds")

add_compile_options(-Wall -Wextra)
file(GLOB_RECURSE SRC_FILES source/*.c)

add_library(${PROJECT_NAME} STATIC ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_subdirectory(tests)
