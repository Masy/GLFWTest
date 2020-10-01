cmake_minimum_required(VERSION 3.17)
project(GLFWTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TEST OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(OpenGL_GL_PREFERENCE LEGACY)

add_subdirectory(deps/glfw)
find_package(OpenGL REQUIRED)

add_executable(GLFWTest main.cpp FThread.cpp FThread.hpp deps/glad/glad.c)

target_include_directories(GLFWTest PUBLIC
        deps/glfw/include
        deps/glad/include)

target_link_libraries(GLFWTest glfw ${OPENGL_gl_LIBRARY})