cmake_minimum_required(VERSION 3.9.2)
project(IHT-2 C)
enable_language(C CXX)

configure_file(CMakeLists.txt.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)

enable_testing()
add_subdirectory(time_test)

set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -std=c11 -Werror -Wall -Wpedantic -fPIC" )

set(CMAKE_C_STANDARD 99)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_library(static_lib STATIC ${PROJECT_SOURCE_DIR}/src/lib_sequintally.c)
add_library(shared_lib SHARED ${PROJECT_SOURCE_DIR}/src/lib_parallel.c)

file(GLOB sources
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.c")

add_executable(${PROJECT_NAME} src/main.c src/lib_realisation.c include/auxiliary_functions.h src/auxiliary_functions.c include/vec_sys_struct.h)

if(UNIX AND NOT APPLE)
    set(CMAKE_REQUIRED_LIBRARIES m)
    target_link_libraries(${PROJECT_NAME} m)
    find_package(Threads REQUIRED)
    target_link_libraries(${PROJECT_NAME} Threads::Threads)
endif()

target_link_libraries(${PROJECT_NAME} static_lib shared_lib)

