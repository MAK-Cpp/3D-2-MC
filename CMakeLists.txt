cmake_minimum_required(VERSION 3.12)

project(3D2MC VERSION 0.0.1 LANGUAGES CXX)

find_package(OpenGL REQUIRED)
find_package(GLFW3 3.3 REQUIRED)
find_package(GLEW REQUIRED)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_CXX_CLANG_TIDY clang-tidy)
# set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    link_libraries(glfw "/Windows/System32/glew32.dll" OpenGL::GL)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
    link_libraries(glfw "/opt/homebrew/Cellar/glew/2.2.0_1/lib/libGLEW.2.2.0.dylib" OpenGL::GL)
endif()

add_subdirectory(lib)
add_subdirectory(src)

#target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_OPT})





