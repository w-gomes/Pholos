cmake_minimum_required(VERSION 3.4..3.15)

project(SQLiteCPP LANGUAGES CXX)

add_library(SQLiteCPP STATIC
    src/Backup.cpp
    src/Column.cpp
    src/Database.cpp
    src/Exception.cpp
    src/Statement.cpp
    src/Transaction.cpp
    )

target_include_directories(SQLiteCPP PRIVATE 
    ${CMAKE_SOURCE_DIR}/Pholos/external
    ${CMAKE_SOURCE_DIR}/Pholos/external/sqlite3
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
