#include <vector>
#include <stdlib.h>
#include <cmath>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

class Circle {
    public:
    GLfloat radius, x, y;
    int res;
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    
    Circle(GLfloat radius, GLfloat x, GLfloat y, int res);
    int getVerticesArraySize();
    int getIndicesArraySize();
    void generateVertices();

    // TODO: a function that draws the circles themselves (move the VBO and VAO to this class)
};