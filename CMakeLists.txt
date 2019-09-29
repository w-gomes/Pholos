cmake_minimum_required(VERSION 3.4..3.15)

project(Pholos LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Pholos/external/fmt)
add_subdirectory(Pholos/external/SQLiteCPP)

set(Pholos_SOURCES
    Pholos/src/main.cpp
    Pholos/src/application.cpp
    Pholos/src/user.cpp
    Pholos/src/tv-show.cpp
    Pholos/src/database.cpp
    Pholos/src/controller.cpp
    Pholos/src/movies.cpp
    )

# Sqlite3
set(SQLITE_INCLUDE Pholos/external/sqlite3)
set(SQLITE_LINK_DIR Pholos/lib)
link_directories(${SQLITE_LINK_DIR})

add_executable(Pholos ${Pholos_SOURCES})
target_compile_options(Pholos PUBLIC /W4)
target_compile_features(Pholos PUBLIC cxx_std_17)
target_include_directories(Pholos PUBLIC Pholos/include ${SQLITE_INCLUDE})
target_link_libraries(Pholos PRIVATE fmt::fmt sqlite3 SQLiteCPP)
