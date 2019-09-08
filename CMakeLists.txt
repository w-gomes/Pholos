cmake_minimum_required(VERSION 3.4..3.15)

project(Pholos LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(external/fmt)

set(Pholos_SOURCES
    Pholos/src/main.cpp
    Pholos/src/application.cpp
    Pholos/src/user.cpp
    Pholos/src/tv-show.cpp
    Pholos/src/database.cpp
    Pholos/src/controller.cpp
    Pholos/src/movies.cpp
    )

link_directories(Pholos/lib)

add_executable(Pholos ${Pholos_SOURCES})
target_compile_options(Pholos PUBLIC /W4)
target_compile_features(Pholos PUBLIC cxx_std_17)
target_include_directories(Pholos PUBLIC Pholos/include Pholos/external/sqlite3)
target_link_libraries(Pholos PRIVATE fmt::fmt sqlite3)
