cmake_minimum_required(VERSION 3.10)

project(SQLiteCPP LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC
    src/Backup.cpp
    src/Column.cpp
    src/Database.cpp
    src/Exception.cpp
    src/Statement.cpp
    src/Transaction.cpp
    )
add_library(SQLiteCPP::${PROJECT_NAME} ALIAS ${PROJECT_NAME})


add_subdirectory(sqlite3)

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    PUBLIC ${PROJECT_SOURCE_DIR}/sqlite3
)
target_link_libraries(${PROJECT_NAME} PUBLIC sqlite3::sqlite3)
