add_executable(${PROJECT_NAME} programm.cpp)


target_link_libraries(${PROJECT_NAME}
        PUBLIC
        shader
        vboindexer
        cube
)

target_include_directories(${PROJECT_NAME} PUBLIC
                          ${PROJECT_SOURCE_DIR}/lib
                          ${PROJECT_SOURCE_DIR}/lib/figures
                          ${PROJECT_SOURCE_DIR}/shaders
                          )
