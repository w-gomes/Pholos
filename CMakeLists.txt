cmake_minimum_required(VERSION 3.10)

project(Pholos LANGUAGES CXX)
include(cmake/standard_project_settings.cmake)
include(cmake/prevent_in_source_builds.cmake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# add fmt library
find_package(fmt REQUIRED)

# Link this 'library' to use the warnings specified in compiler_warnings.cmake
add_library(project_warnings INTERFACE)
include(cmake/compiler_warnings.cmake)
set_project_warnings(project_warnings)

# static analyzers
include(cmake/static_analyzers.cmake)

option(ENABLE_TEST "Enable Test" ON)

add_subdirectory(Pholos/external/SQLiteCPP)

set(Pholos_SOURCES
    Pholos/src/main.cpp
    Pholos/src/application.cpp
    Pholos/src/tv-show.cpp
    Pholos/src/database.cpp
    Pholos/src/controller.cpp
    Pholos/src/movies.cpp
    Pholos/src/content-base.cpp
    Pholos/src/internal.cpp
    )

add_executable(${PROJECT_NAME} ${Pholos_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC Pholos/src)
target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE project_warnings
  PUBLIC fmt::fmt-header-only
          SQLiteCPP::SQLiteCPP
)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

if(ENABLE_TEST)
  enable_testing()
  message("Building tests")
  add_subdirectory(Pholos/test)
endif()
