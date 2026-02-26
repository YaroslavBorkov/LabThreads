cmake_minimum_required(VERSION 3.16)
project(lab2_3mod LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab2_3mod
    src/main.cpp
    src/parser.cpp
    src/writer.cpp
)

target_include_directories(lab2_3mod PRIVATE src)
