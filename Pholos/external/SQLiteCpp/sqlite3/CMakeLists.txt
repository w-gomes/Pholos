cmake_minimum_required(VERSION 3.10)

project(sqlite3 LANGUAGES C)

add_library(${PROJECT_NAME} STATIC
    sqlite3.c
)
add_library(sqlite3::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC sqlite3.h)
