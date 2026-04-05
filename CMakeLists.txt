cmake_minimum_required(VERSION 3.31)

project(cppKillteam LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_STANDARD 20)

add_compile_options(-Wall -Wextra -Wconversion -Wshadow)

add_subdirectory(src/game)
add_subdirectory(src)

enable_testing()
add_subdirectory(test)