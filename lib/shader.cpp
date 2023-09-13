#include "shader.hpp"

GLuint LoadShaders(const std::filesystem::path& vertex_file_path, const std::filesystem::path& fragment_file_path) {
    // Create the shaders
    GLuint vertex_shader_id   = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    std::string vertex_shader_code;
    std::ifstream vertex_shader_stream(vertex_file_path, std::ios::in);
    if (vertex_shader_stream.is_open()) {
        std::stringstream string_stream;
        string_stream << vertex_shader_stream.rdbuf();
        vertex_shader_code = string_stream.str();
        vertex_shader_stream.close();
    } else {
        std::cerr << "Impossible to open " << vertex_file_path.c_str()
                  << ". Are you in the right directory ? Don't "
                     "forget to read the FAQ !\n";
        getchar();
        return 0;
    }

    // Read the Fragment Shader code from the file
    std::string fragment_shader_code;
    std::ifstream fragment_shader_stream(fragment_file_path, std::ios::in);
    if (fragment_shader_stream.is_open()) {
        std::stringstream string_stream;
        string_stream << fragment_shader_stream.rdbuf();
        fragment_shader_code = string_stream.str();
        fragment_shader_stream.close();
    }

    GLint result = GL_FALSE;
    int info_log_length;

    // Compile Vertex Shader
    std::cout << "Compiling shader : " << vertex_file_path.c_str() << '\n';
    char const* VertexSourcePointer = vertex_shader_code.c_str();
    glShaderSource(vertex_shader_id, 1, &VertexSourcePointer, nullptr);
    glCompileShader(vertex_shader_id);

    // Check Vertex Shader
    glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertex_shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
    if (info_log_length > 0) {
        char vertex_shader_error_message[info_log_length + 1];
        glGetShaderInfoLog(vertex_shader_id, info_log_length, nullptr, vertex_shader_error_message);
        std::cerr << vertex_shader_error_message << '\n';
    }

    // Compile Fragment Shader
    std::cerr << "Compiling shader : " << fragment_file_path.c_str() << '\n';
    char const* fragment_source_pointer = fragment_shader_code.c_str();
    glShaderSource(fragment_shader_id, 1, &fragment_source_pointer, nullptr);
    glCompileShader(fragment_shader_id);

    // Check Fragment Shader
    glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragment_shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
    if (info_log_length > 0) {
        char fragment_shader_error_message[info_log_length + 1];
        glGetShaderInfoLog(fragment_shader_id, info_log_length, nullptr, fragment_shader_error_message);
        std::cout << fragment_shader_error_message << '\n';
    }

    // Link the program
    std::cout << "Linking program\n";
    GLuint program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);
    glLinkProgram(program_id);

    // Check the program
    glGetProgramiv(program_id, GL_LINK_STATUS, &result);
    glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);
    if (info_log_length > 0) {
        char program_error_message[info_log_length + 1];
        glGetProgramInfoLog(program_id, info_log_length, nullptr, program_error_message);
        std::cerr << program_error_message << '\n';
    }
    glDetachShader(program_id, vertex_shader_id);
    glDetachShader(program_id, fragment_shader_id);

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    return program_id;
}
