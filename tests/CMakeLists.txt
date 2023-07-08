cmake_minimum_required(VERSION 3.20)
project(gencds_tests)

file(GLOB_RECURSE SRC_FILES source/*_tests.c)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} criterion)
target_link_libraries(${PROJECT_NAME} gencds)
target_include_directories(${PROJECT_NAME} PUBLIC
    ../include
)

add_custom_target(tests_run
    COMMAND tests/${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
