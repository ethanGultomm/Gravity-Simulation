#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <iostream>
#include <chrono>
#include <vector>
#include <stdlib.h>
#include <cmath>

#include "circle.h"
using namespace std;

static void error_callback(int error, const char* description){
    fprintf(stderr, "Error: %s\n", description);
}

void processInput(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
    // update projection
    Circle* c = static_cast<Circle*>(glfwGetWindowUserPointer(window));
    if(c)
        c->setProjection((float)width, (float)height);
}

int main(){
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLfloat windowWidth = 1000.0f;
    GLfloat windowHeight = 800.0f;

    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "cock-and-ball-inator 3000", NULL, NULL);
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

    glViewport(0, 0, windowWidth, windowHeight);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // draw a circle with a given resolution
    int const res = 50;
    std::vector<GLfloat> center = {0.0f, 0.0f, 0.0f};
    GLfloat radius = 30.0f;    // value in pixels
    radius = radius / (windowHeight / 2);   //convert to absolute value (0.0 - 1.0)

    // creating the circle object
    Circle ballknowledge(radius, center[0], center[1], res);
    ballknowledge.setProjection(windowWidth, windowHeight);
    glfwSetWindowUserPointer(window, &ballknowledge);

    double prevTime = glfwGetTime();
    const double frameTime = 1.0 / 60;  // 60hz

    // MAIN RENDER LOOP
    while (!glfwWindowShouldClose(window)){
        // input
        processInput(window);
        // render commands here
        glClearColor(0.12f, 0.12f, 0.12f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        double currentTime = glfwGetTime();
        if(currentTime - prevTime >= frameTime){
            //center[0] += 0.001f;
            //center[1] += 0.002;
            prevTime += frameTime;
        }

        ballknowledge.draw(center[0], center[1]);

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_FAILURE);
}