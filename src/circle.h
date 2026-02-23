#pragma once
#include <vector>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

#include <shape.h>

class Circle : public Shape{
  private:
    int res;
    std::vector<float> vertices;
    std::vector<uint32_t>indices;
    uint32_t VAO, VBO, EBO, shaderProgram, modelLoc, projLoc;
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
    float radius;
    Circle(float radius, int res);
    ~Circle() override;
    void init();
    void generateVertices();
    void draw(const glm::vec2& position) override;
    void setProjection(float width, float height) override;
};