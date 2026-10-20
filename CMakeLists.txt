cmake_minimum_required(VERSION 3.10)

project(cpp-networks-and-reverse-engineering)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(game
    src/main.cpp
    src/Input.cpp
    src/Map.cpp
)

target_include_directories(game PRIVATE include)
