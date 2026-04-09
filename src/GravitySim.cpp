#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <iostream>
#include <chrono>
#include <vector>
#include <stdlib.h>
#include <cmath>

#include <world.h>
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
    auto* world = static_cast<World*>(glfwGetWindowUserPointer(window));

    if(world){
        world->setProjection((float)width, (float)height);
    }
}

int main(){
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLfloat windowWidth = 1300.0f;
    GLfloat windowHeight = 1000.0f;

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

    // the circles parameters
    int const res = 50;
    GLfloat radius = 20.0f;    // value in pixels
    radius = radius / (windowHeight / 2);   //convert to absolute value (0.0 - 1.0)

    // creating one ball
    World world;
    glfwSetWindowUserPointer(window, &world);

    // add one circle object to balls, this will be the one that moves
    // world.addCircle(radius, 0.0f, 0.0f, res, windowWidth, windowHeight, glm::vec2(0.01f, 0.05f));

    double prevTime = glfwGetTime();
    const double frameTime = 1.0 / 60;  // 60hz
    int ballsCount = 0;
    int frameCount = 0;
    int angleCount = 0;
    // MAIN LOOP
    while (!glfwWindowShouldClose(window)){
        // input
        processInput(window);

        // create 5 balls and put them all in the balls vector
        // if(ballsCount < 5){
        //     world.addCircle(radius, spawnCenter[0], spawnCenter[1], res, windowWidth, windowHeight, glm::vec2(0.0f, 0.0f));
        //     spawnCenter[0] += 0.2;
        //     ballsCount++;
        // }

        double currentTime = glfwGetTime();
        // updates eevery frameTime
        if ((currentTime - prevTime) >= frameTime){
            // render commands here
            glClearColor(0.12f, 0.12f, 0.12f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            if(frameCount == 4){
                glm::vec2 velocity;
                float angle = 2.0f * 3.14159265359 * (static_cast<float>(angleCount) / 30);
                velocity.x = cos(angle) * 0.04;
                velocity.y = sin(angle) * 0.04;
                world.addCircle(radius, 0.0f, 0.0f, res, windowWidth, windowHeight, velocity);
                angleCount++;
                frameCount = 0;
            }
            
            world.update(frameTime);
            world.render();
            prevTime = glfwGetTime();

            // check and call events and swap the buffers
            glfwSwapBuffers(window);
            glfwPollEvents();
            frameCount++;
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_FAILURE);
}

// TODO: 
// -create a physics module that will contain all phyics