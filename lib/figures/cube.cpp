#include "cube.h"

GLuint figure::Cube::vertex_array_object_   = 0;
GLuint figure::Cube::vertex_buffer_object_  = 0;
GLuint figure::Cube::element_buffer_object_ = 0;
GLuint figure::Cube::color_buffer_object_   = 0;

static constexpr glm::mat4 kIdentityMatrix(1);

figure::Cube::Cube(GLfloat const var_x, GLfloat const var_y, GLfloat const var_z)
    : model_(glm::translate(kIdentityMatrix, glm::vec3(var_x, var_y, var_z)))
    , x{model_[3][0]}
    , y{model_[3][1]}
    , z{model_[3][2]} {}

figure::Cube::Cube(glm::vec3 const& coordinates)
    : model_(glm::translate(kIdentityMatrix, coordinates)), x{model_[3][0]}, y{model_[3][1]}, z{model_[3][2]} {}

figure::Cube::Cube(figure::Cube const& other)
    : model_(other.model_), x{model_[3][0]}, y{model_[3][1]}, z{model_[3][2]} {}

figure::Cube::~Cube() = default;

figure::Cube& figure::Cube::operator=(figure::Cube const& other) {
    model_ = other.model_;

    return *this;
}

const glm::mat4& figure::Cube::model() const noexcept {
    return model_;
}
glm::vec3 figure::Cube::coordinates() const noexcept {
    return {x, y, z};
}

void figure::Cube::Draw() const {
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBindVertexArray(vertex_array_object_);
    // Draw the triangle !
    glDrawElements(GL_TRIANGLES, 3 * 12, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
void figure::Cube::generateBuffers() {
    std::cout << "Generate buffers for cube... ";
    glGenVertexArrays(1, &vertex_array_object_);
    glBindVertexArray(vertex_array_object_);

    glGenBuffers(1, &vertex_buffer_object_);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object_);
    // Give our vertices to OpenGL.

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_STATIC_DRAW);

    glGenBuffers(1, &element_buffer_object_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0,                            // 1) attribute 0. No particular reason for 0,
                                                        //    but must match the layout in the shader.
                          3,                            // 2) size
                          GL_FLOAT,                     // 3) type
                          GL_FALSE,                     // 4) normalized?
                          0,                            // 5) stride
                          reinterpret_cast<GLvoid*>(0)  // 6) array buffer offset
    );
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &color_buffer_object_);
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer_object_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1,                            // 1) attribute 1. No particular reason for 1, but
                                                        //    must match the layout in the shader.
                          3,                            // 2) size
                          GL_FLOAT,                     // 3) type
                          GL_FALSE,                     // 4) normalized?
                          0,                            // 5) stride
                          reinterpret_cast<GLvoid*>(0)  // 6) array buffer offset
    );
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    std::cout << "Done!\n";
}
void figure::Cube::clearBuffers() {
    std::cout << "Clear cube buffers... ";
    glDeleteBuffers(1, &vertex_buffer_object_);
    glDeleteBuffers(1, &color_buffer_object_);
    glDeleteBuffers(1, &element_buffer_object_);
    glDeleteVertexArrays(1, &vertex_array_object_);
    std::cout << "Done!\n";
}
figure::Cube& figure::Cube::operator+=(glm::vec3 const& vector) {
    x += vector.x;
    y += vector.y;
    z += vector.z;
    return *this;
}
