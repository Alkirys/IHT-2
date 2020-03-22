include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/src")

file(GLOB sources
        "${PROJECT_SOURCE_DIR}/*/*.c"
        "${PROJECT_SOURCE_DIR}/*/*.cpp"
        "${PROJECT_SOURCE_DIR}/*/*.h")
list(REMOVE_ITEM sources "${PROJECT_SOURCE_DIR}/src/main.c")

file(GLOB tests "${PROJECT_SOURCE_DIR}/time_test/*.cpp")
list(REMOVE_ITEM tests "${PROJECT_SOURCE_DIR}/time_test/main.cpp")

foreach(file ${tests})
    set(name)
    get_filename_component(name ${file} NAME_WE)
    add_executable("${name}_tests"
            ${sources}
            ${file}
            "${PROJECT_SOURCE_DIR}/time_test/main.cpp")
    target_link_libraries("${name}_tests" gtest_main)
    add_test(NAME ${name} COMMAND "${name}_tests")
endforeach()
