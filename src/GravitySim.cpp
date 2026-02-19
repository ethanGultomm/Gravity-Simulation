#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <cmath>
using namespace std;;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.96f, 0.19f, 0.29f, 1.0f);\n"
"}\n\0";

static void error_callback(int error, const char* description){
    fprintf(stderr, "Error: %s\n", description);
}

void processInput(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}

int main(){
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 800, "cock-and-ball-inator 3000", NULL, NULL);
    if (!window){
        glfwTerminate();
        cerr << "creating window failed" << endl;
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        cerr << "failed to initialize glad" << endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwSwapInterval(1);

    // vertices for a right triangle
    GLfloat vertices[] = 
    {
        0.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    // draw a circle with a given resolution
    int const res = 50;
    std::vector<GLfloat> center = {0.0f, 0.0f, 0.0f};
    GLfloat radius = 0.3f;

    GLfloat circleVertices[(res+1)*3];
    circleVertices[0] = center[0];
    circleVertices[1] = center[1];
    circleVertices[2] = center[2];
    GLuint indices[res*3];

    for (size_t i = 0; i < res; i++)
    {
        // calculate the next vertex with trigonometry
        GLfloat angle = 2.0f * 3.14159265359 * (static_cast<float>(i) / res);
        GLfloat x = center[0] + cos(angle) * radius;
        GLfloat y = center[1] + sin(angle) * radius;
        // save the vertex, its i+1 because index 0 is already used by the center point
        circleVertices[(i+1)*3] = x;
        circleVertices[((i+1)*3)+1] = y;
        circleVertices[((i+1)*3)+2] = 0.0f; // since we're working with 2d, Z axis stays at 0

        // make the indices, look at sketch.jpg for uhh some kinda explanation lol
        indices[i*3]     = 0;   // indice a
        indices[(i*3)+1] = i+1; // indice b
        indices[(i*3)+2] = i+2; // indice c
    }
    indices[(res*3)-1] = 1; // connects the last triangle to the first vertex

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    GLuint VAO, VBO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(circleVertices), circleVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    int success;
    char infolog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
        std::cout << "there's a vertex shader error twin, fix ts twin:\n" << infolog << std::endl;
    }

    // MAIN RENDER LOOP
    while (!glfwWindowShouldClose(window)){
        // input
        processInput(window);
        // render commands here
        glClearColor(0.12f, 0.12f, 0.12f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, res*3, GL_UNSIGNED_INT, 0);

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_FAILURE);
}