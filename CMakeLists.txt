cmake_minimum_required(VERSION 3.9.2)
project(IHT-2 C)
enable_language(C CXX ASM)

set(CMAKE_REQUIRED_LIBRARIES m)
set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -std=c11 -Werror -Wall -Wpedantic -fPIC" )

set(CMAKE_C_STANDARD 99)


include_directories("${PROJECT_SOURCE_DIR}/include")

add_library(static_lib STATIC ${PROJECT_SOURCE_DIR}/src/lib_sequintally.c)
add_library(shared_lib SHARED ${PROJECT_SOURCE_DIR}/src/lib_parallel.c)

file(GLOB sources
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.c")

add_executable(${PROJECT_NAME} ${sources})

find_package(Threads REQUIRED)

target_link_libraries(${PROJECT_NAME} m)
target_link_libraries(${PROJECT_NAME} Threads::Threads)
target_link_libraries(${PROJECT_NAME} Threads::Threads static_lib shared_lib)
