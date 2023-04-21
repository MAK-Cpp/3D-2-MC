configure_file (${PROJECT_SOURCE_DIR}/lib/config.h.in ${PROJECT_SOURCE_DIR}/lib/config.h @ONLY)

add_library(shader shader.cpp shader.hpp)
add_library(controls controls.cpp controls.hpp)
add_library(objloader objloader.cpp objloader.hpp)
add_library(quaternion_utils quaternion_utils.cpp quaternion_utils.hpp)
add_library(tangentspace tangentspace.cpp tangentspace.hpp)
add_library(text2D text2D.cpp text2D.hpp)
add_library(texture texture.cpp texture.hpp)
add_library(vboindexer vboindexer.cpp vboindexer.hpp)


add_subdirectory(figures)
