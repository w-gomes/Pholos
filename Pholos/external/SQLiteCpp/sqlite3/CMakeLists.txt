cmake_minimum_required(VERSION 3.10)

project(sqlite3 LANGUAGES C)

add_library(sqlite3 STATIC
    sqlite3.c
)
add_library(sqlite3::sqlite3 ALIAS sqlite3)

target_include_directories(sqlite3 PUBLIC sqlite3.h)
