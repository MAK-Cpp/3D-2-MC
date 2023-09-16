#ifndef GL_FIGURE_CUBE
#define GL_FIGURE_CUBE

#include <iostream>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include Graphic Library Math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

namespace figure {

class Cube {
private:
    // Our vertices. Three consecutive floats give a 3D vertex; Three
    // consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles,
    // and 12*3 vertices
    static constexpr GLfloat vertexes[] = {-0.5, -0.5, -0.5, -0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5,
                                           0.5,  -0.5, -0.5, 0.5,  0.5, -0.5, 0.5,  0.5, 0.5, 0.5,  -0.5, 0.5};
    static constexpr GLfloat colors[]   = {0.583, 0.771, 0.014, 0.310, 0.747, 0.185,  0.327,  0.483,
                                           0.844, 0.609, 0.115, 0.436, 0.359, 0.583,  0.152,  0.822,
                                           0.569, 0.201, 0.279, 0.317, 0.505, 0.597f, 0.770f, 0.761f};
    static constexpr GLuint indices[]   = {0, 3, 2, 5, 0, 1, 7, 0, 4, 5, 4, 0, 0, 2, 1, 7, 3, 0,
                                           2, 3, 7, 6, 4, 5, 4, 6, 7, 6, 5, 1, 6, 1, 2, 6, 2, 7};

    static GLuint vertex_array_object_;
    static GLuint vertex_buffer_object_;
    static GLuint element_buffer_object_;
    static GLuint color_buffer_object_;

    glm::mat4 model_;

public:
    GLfloat &x, y, z;

    explicit Cube(GLfloat const = 0, GLfloat const = 0, GLfloat const = 0);
    explicit Cube(glm::vec3 const&);
    Cube(figure::Cube const&);
    ~Cube();

    Cube& operator=(figure::Cube const&);
    Cube& operator+=(glm::vec3 const&);

    [[nodiscard]] const glm::mat4& model() const noexcept;
    [[nodiscard]] glm::vec3 coordinates() const noexcept;

    static void generateBuffers();
    static void clearBuffers();

    void Draw() const;
};

}  // namespace figure

#endif