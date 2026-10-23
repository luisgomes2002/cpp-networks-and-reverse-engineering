cmake_minimum_required(VERSION 3.20)

project(cpp-networks-and-reverse-engineering LANGUAGES C CXX)

if(POLICY CMP0072)
	cmake_policy(SET CMP0072 NEW)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 QUIET)

include(FetchContent)

if(NOT glfw3_FOUND)
	FetchContent_Declare(
		glfw
		URL https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.zip)
	FetchContent_MakeAvailable(glfw)
endif()

FetchContent_Declare(
	glad
	GIT_REPOSITORY https://github.com/Dav1dde/glad.git
	GIT_TAG v2.0.8
	GIT_SHALLOW TRUE)
FetchContent_Populate(glad)
add_subdirectory(${glad_SOURCE_DIR}/cmake ${glad_BINARY_DIR})
glad_add_library(glad_gl_core_33 REPRODUCIBLE API gl:core=3.3)

add_executable(game
    src/app/main.cpp
    engine/src/core/mat4.cpp
    engine/src/rendering/opengl_renderer.cpp
    engine/src/rendering/shader_program.cpp
    engine/src/rendering/primitives/cube_mesh.cpp
    engine/src/rendering/primitives/rectangle_mesh.cpp
    game/src/systems/game.cpp
)

target_include_directories(game PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/include
    ${CMAKE_CURRENT_SOURCE_DIR}/game/include
)

target_link_libraries(game PRIVATE OpenGL::GL)
target_link_libraries(game PRIVATE glad_gl_core_33)

if(TARGET glfw)
	target_link_libraries(game PRIVATE glfw)
elseif(TARGET glfw3::glfw)
	target_link_libraries(game PRIVATE glfw3::glfw)
else()
	message(FATAL_ERROR "A biblioteca GLFW não foi encontrada.")
endif()
