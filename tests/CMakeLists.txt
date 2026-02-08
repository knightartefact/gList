cmake_minimum_required(VERSION 3.20)
project(glist_tests)

include(CTest)

file(GLOB_RECURSE SRC_FILES source/*_tests.c)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} criterion)
target_link_libraries(${PROJECT_NAME} glist)

add_test(
    NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tests
)

