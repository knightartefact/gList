cmake_minimum_required(VERSION 3.20)
project(glist_tests)

include(CTest)

set(SRC_FILES
    source/glist_back_tests.c
    source/glist_front_tests.c
    source/glist_popback_tests.c
    source/glist_popfront_tests.c
    source/glist_print_tests.c
    source/glist_pushback_tests.c
    source/glist_pushfront_tests.c
    source/glist_sort_tests.c
    source/glist_tests.c
)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_compile_options(${PROJECT_NAME} PRIVATE -g3)

target_link_libraries(${PROJECT_NAME}
    criterion
    glist
)

add_test(
    NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tests
)

