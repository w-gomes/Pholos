project(Tests LANGUAGES CXX)

set(TEST_SOURCES 
    main.cpp
)

add_executable(Tests ${TEST_SOURCES})
target_compile_options(Tests PRIVATE /W4)
target_include_directories(Tests PRIVATE ../include)
