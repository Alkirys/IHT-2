cmake_minimum_required(VERSION 3.9.2)
project(IHT-2 C)
enable_language(C CXX)

set(CMAKE_C_STANDARD 99)


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

set(lib_static_hdrs
        ${PROJECT_SOURCE_DIR}/include/lib_realisation.h
        ${PROJECT_SOURCE_DIR}/include/lib_sequintally.h
        )

set(lib_static_srcs
        ${PROJECT_SOURCE_DIR}/src/lib_realisation.c
        ${PROJECT_SOURCE_DIR}/src/lib_sequintally.c
        )


add_library( static_lib STATIC ${lib_static_srcs} ${lib_static_hdrs} )

set(lib_shared_hdrs
        ${PROJECT_SOURCE_DIR}/include/lib_realisation.h
        ${PROJECT_SOURCE_DIR}/include/lib_parallel.h
        )
set(lib_shared_srcs
        ${PROJECT_SOURCE_DIR}/src/lib_realisation.c
        ${PROJECT_SOURCE_DIR}/src/lib_parallel.c
        )

add_library( shared_lib SHARED ${lib_shared_srcs} ${lib_shared_hdrs} )

if(UNIX AND NOT APPLE)
    set(CMAKE_REQUIRED_LIBRARIES m)
    target_link_libraries(static_lib m)
    target_link_libraries(shared_lib m)
    find_package(Threads REQUIRED)
    target_link_libraries(shared_lib Threads::Threads)
endif()

add_executable(${PROJECT_NAME} src/main.c src/auxiliary_functions.c)

target_link_libraries(${PROJECT_NAME} static_lib shared_lib)
