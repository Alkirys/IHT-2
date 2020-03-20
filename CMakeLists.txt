cmake_minimum_required(VERSION 3.9.2)
project(IHT-2 C)
enable_language(C)

set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -std=c11 -Werror -Wall -Wpedantic -fPIC" )

set(CMAKE_C_STANDARD 99)

SET(CMAKE_C_ARCHIVE_CREATE   "<CMAKE_AR> Scr <TARGET> <LINK_FLAGS> <OBJECTS>")
SET(CMAKE_CXX_ARCHIVE_CREATE "<CMAKE_AR> Scr <TARGET> <LINK_FLAGS> <OBJECTS>")
SET(CMAKE_C_ARCHIVE_FINISH   "<CMAKE_RANLIB> -no_warning_for_no_symbols -c <TARGET>")
SET(CMAKE_CXX_ARCHIVE_FINISH "<CMAKE_RANLIB> -no_warning_for_no_symbols -c <TARGET>")

include_directories("${PROJECT_SOURCE_DIR}/include")

add_library(static_lib STATIC ${PROJECT_SOURCE_DIR}/src/lib_sequintally.c)
add_library(shared_lib SHARED ${PROJECT_SOURCE_DIR}/src/lib_parallel.c)

file(GLOB sources
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.c")

add_executable(${PROJECT_NAME} ${sources})

if(UNIX AND NOT APPLE)
    set(CMAKE_REQUIRED_LIBRARIES m)
    target_link_libraries(${PROJECT_NAME} m)
    find_package(Threads REQUIRED)
    target_link_libraries(${PROJECT_NAME} Threads::Threads)
endif()

target_link_libraries(${PROJECT_NAME} static_lib shared_lib)
