#ifndef GL_PRIMITIVE_POINT
#define GL_PRIMITIVE_POINT

#include "GL/glew.h"
#include "glm/glm.hpp"

class Point {
private:
    GLfloat x_;
    GLfloat y_;
    GLfloat z_;
public:
    explicit Point(GLfloat, GLfloat, GLfloat);
    explicit Point(glm::vec3 const&);
    Point(Point const&);

    Point& operator=(Point const&);
};

#endif
