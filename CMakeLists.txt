cmake_minimum_required(VERSION 3.12)

project(3D2MC VERSION 0.0.1 LANGUAGES CXX)

find_package(OpenGL REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add_subdirectory(lib)
add_subdirectory(src)



set(COMPILE_OPT -Werror -Wall -Wextra)
target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_OPT})


