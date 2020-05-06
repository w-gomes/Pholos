cmake_minimum_required(VERSION 3.10)

project(SQLiteCPP LANGUAGES CXX)

add_library(SQLiteCPP STATIC
    src/Backup.cpp
    src/Column.cpp
    src/Database.cpp
    src/Exception.cpp
    src/Statement.cpp
    src/Transaction.cpp
    )
add_library(SQLiteCPP::SQLiteCPP ALIAS SQLiteCPP)


add_subdirectory(sqlite3)

target_include_directories(SQLiteCPP 
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    PUBLIC ${PROJECT_SOURCE_DIR}/sqlite3
)
target_link_libraries(SQLiteCPP PUBLIC sqlite3::sqlite3)
