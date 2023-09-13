#include "Point.h"

Point::Point(GLfloat x, GLfloat y, GLfloat z): x_{x}, y_{y}, z_{z} {}
Point::Point(glm::vec3 const& coordinates): x_{coordinates.x}, y_{coordinates.y}, z_{coordinates.z} {}
Point::Point(Point const& other) = default;

Point& Point::operator=(Point const& other) = default;

