#include "cube.h"

static constexpr glm::mat4 kIdentityMatrix(1);

figure::Cube::Cube(GLfloat const x, GLfloat const y, GLfloat const z)
    : model_(glm::translate(kIdentityMatrix, glm::vec3(x, y, z))), X{model_[3][0]}, Y{model_[3][1]}, Z{model_[3][2]} {
    glGenVertexArrays(1, &vertex_array_id_);
    glBindVertexArray(vertex_array_id_);

    glGenBuffers(1, &vertex_buffer_);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    glVertexAttribPointer(0,                            // 1) attribute 0. No particular reason for 0,
                                                        //    but must match the layout in the shader.
                          3,                            // 2) size
                          GL_FLOAT,                     // 3) type
                          GL_FALSE,                     // 4) normalized?
                          0,                            // 5) stride
                          reinterpret_cast<GLvoid*>(0)  // 6) array buffer offset
    );
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &color_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
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
}

figure::Cube::Cube(glm::vec3 const& xyz)
    : model_(glm::translate(kIdentityMatrix, xyz)), X(model_[3][0]), Y(model_[3][1]), Z(model_[3][2]) {
    glGenVertexArrays(1, &vertex_array_id_);
    glBindVertexArray(vertex_array_id_);

    glGenBuffers(1, &vertex_buffer_);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    glVertexAttribPointer(0,                            // 1) attribute 0. No particular reason for 0,
                                                        //    but must match the layout in the shader.
                          3,                            // 2) size
                          GL_FLOAT,                     // 3) type
                          GL_FALSE,                     // 4) normalized?
                          0,                            // 5) stride
                          reinterpret_cast<GLvoid*>(0)  // 6) array buffer offset
    );
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &color_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
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
}

figure::Cube::Cube(figure::Cube const& other)
    : model_(other.model_), X(model_[3][0]), Y(model_[3][1]), Z(model_[3][2]) {
    glGenVertexArrays(1, &vertex_array_id_);
    glBindVertexArray(vertex_array_id_);

    glGenBuffers(1, &vertex_buffer_);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    glVertexAttribPointer(0,                            // 1) attribute 0. No particular reason for 0,
                                                        //    but must match the layout in the shader.
                          3,                            // 2) size
                          GL_FLOAT,                     // 3) type
                          GL_FALSE,                     // 4) normalized?
                          0,                            // 5) stride
                          reinterpret_cast<GLvoid*>(0)  // 6) array buffer offset
    );
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &color_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
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
}

figure::Cube::~Cube() {
    glDeleteVertexArrays(1, &vertex_array_id_);
    glDeleteBuffers(1, &vertex_buffer_);
    glDeleteBuffers(1, &color_buffer_);
}

figure::Cube& figure::Cube::operator=(figure::Cube const& other) {
    model_ = other.model_;

    return *this;
}

const glm::mat4& figure::Cube::model() const {
    return model_;
}

void figure::Cube::Draw() const {
    glBindVertexArray(vertex_array_id_);
    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3 * 12);  // Starting from vertex 0; 3 * 12 vertices total -> 12 triangles
    glBindVertexArray(0);
}