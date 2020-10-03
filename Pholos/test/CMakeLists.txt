project(Tests LANGUAGES CXX)

find_package(Catch2 REQUIRED)

set(Test_SOURCES
    main_catch.cpp
    test_dummy.cpp
)

add_executable(${PROJECT_NAME} ${Test_SOURCES})
target_link_libraries(${PROJECT_NAME} Catch2::Catch2)

include(CTest)
include(Catch)
# for catch to discover TEST_CASE
catch_discover_tests(Tests)
