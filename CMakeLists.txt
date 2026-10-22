cmake_minimum_required(VERSION 3.10)

project(cpp-networks-and-reverse-engineering)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(game
    src/app/main.cpp
    engine/src/collision.cpp
    engine/src/input.cpp
    engine/src/map.cpp
    game/src/combat.cpp
    game/src/game.cpp
)

target_include_directories(game PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/include
    ${CMAKE_CURRENT_SOURCE_DIR}/game/include
)
