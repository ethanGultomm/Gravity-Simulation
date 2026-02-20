#include <vector>
#include <stdlib.h>
#include <cmath>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

class Circle {
  private:
    GLfloat radius, x, y;
    int res;
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    GLuint VAO, VBO, EBO, shaderProgram, modelLoc, projLoc;
    const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "uniform mat4 model;\n"
    "uniform mat4 projection;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = projection * model * vec4(aPos, 1.0);\n"
    "}\0";
    const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "	FragColor = vec4(0.96f, 0.19f, 0.29f, 1.0f);\n"
    "}\n\0";

  public:
    Circle(GLfloat radius, GLfloat x, GLfloat y, int res);
    ~Circle();
    void init();
    void generateVertices();
    void draw(GLfloat newX, GLfloat newY);
    void setProjection(float width, float height);
};