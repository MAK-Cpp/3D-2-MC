cmake_minimum_required(VERSION 3.12)

project(3D2MC VERSION 0.0.1 LANGUAGES CXX)

find_package(OpenGL REQUIRED)
find_package(GLFW3 3.3 REQUIRED)
find_package(GLM REQUIRED)
find_package(GLEW REQUIRED)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

link_libraries(glfw glew OpenGL::GL)

# set(CMAKE_CXX_CLANG_TIDY clang-tidy)
# set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*")

add_subdirectory(lib)
add_subdirectory(src)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(COMPILE_OPT -Werror -Wall -Wextra)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
#    set(COMPILE_OPT -L/usr/local/lib -lglfw -lglew -framework OpenGL)
endif()
#set(COMPILE_OPT -Werror -Wall -Wextra)
#[[set(LINK_OPTIONS
        /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk
        -Wl,-search_paths_first
        -Wl,-headerpad_max_install_names
        ./src/CMakeFiles/3D2MC.dir/programm.cpp.o
        -o ./src/3D2MC
        -Wl,-rpath,/opt/homebrew/lib
        /opt/homebrew/lib/libGLEW.dylib
        /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd  .
        ./lib/libshader.a
        ./lib/libcontrols.a
        ./lib/libobjloader.a
        ./lib/libquaternion_utils.a
        ./lib/libtangentspace.a
        ./lib/libtext2D.a
        ./lib/libtexture.a
        ./lib/libvboindexer.a
        ./lib/figures/libcube.a
        /opt/homebrew/lib/libglfw.3.3.dylib
        /opt/homebrew/lib/libGLEW.dylib
        /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd)
target_link_options(${PROJECT_NAME} PRIVATE ${LINK_OPTIONS})
target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_OPT})]]





