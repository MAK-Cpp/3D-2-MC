#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

GLuint LoadShaders(const std::filesystem::path& vertex_file_path, const std::filesystem::path& fragment_file_path);

#endif
