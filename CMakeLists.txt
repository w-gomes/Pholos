cmake_minimum_required(VERSION 3.10)

project(Pholos LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_TEST "Enable Test" ON)

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
    Pholos/src/common.cpp
    )

add_executable(Pholos ${Pholos_SOURCES})
target_include_directories(Pholos PUBLIC Pholos/include Pholos/external/SQLiteCpp/include)
# copied from https://github.com/lefticu/cpp_starter_project
target_compile_options(Pholos PUBLIC 
                       /W4
                       /w14242 # 'identfier': conversion from 'type1' to 'type1', possible loss
                               # of data
                       /w14254 # 'operator': conversion from 'type1:field_bits' to
                               # 'type2:field_bits', possible loss of data
                       /w14263 # 'function': member function does not override any base class
                               # virtual member function
                       /w14265 # 'classname': class has virtual functions, but destructor is not
                               # virtual instances of this class may not be destructed correctly
                       /w14287 # 'operator': unsigned/negative constant mismatch
                       /we4289 # nonstandard extension used: 'variable': loop control variable
                               # declared in the for-loop is used outside the for-loop scope
                       /w14296 # 'operator': expression is always 'boolean_value'
                       /w14311 # 'variable': pointer truncation from 'type1' to 'type2'
                       /w14545 # expression before comma evaluates to a function which is missing
                               # an argument list
                       /w14546 # function call before comma missing argument list
                       /w14547 # 'operator': operator before comma has no effect; expected
                               # operator with side-effect
                       /w14549 # 'operator': operator before comma has no effect; did you intend
                               # 'operator'?
                       /w14555 # expression has no effect; expected expression with side- effect
                       /w14619 # pragma warning: there is no warning number 'number'
                       /w14640 # Enable warning on thread un-safe static member initialization
                       /w14826 # Conversion from 'type1' to 'type_2' is sign-extended. This may
                               # cause unexpected runtime behavior.
                       /w14905 # wide string literal cast to 'LPSTR'
                       /w14906 # string literal cast to 'LPWSTR'
                       /w14928 # illegal copy-initialization; more than one user-defined
                              # conversion has been implicitly applied
                       )
target_link_libraries(Pholos PRIVATE fmt::fmt SQLiteCPP sqlite3)
target_compile_features(Pholos PUBLIC cxx_std_17)

if(ENABLE_TEST)
  enable_testing()
  message("Building tests")
  add_subdirectory(Pholos/test)
endif()
