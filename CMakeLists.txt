cmake_minimum_required(VERSION 3.31)

project(cppKillteam LANGUAGES CXX)

set(CXX_STANDARD_REQUIRED YES)
set(CXX_STANDARD 20)

add_compile_options(-Wall -Wextra -Wconversion -Wshadow)

add_subdirectory(src)

enable_testing()