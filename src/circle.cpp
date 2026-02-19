#include "circle.h"

Circle::Circle(GLfloat radius, GLfloat x, GLfloat y, int res){
    this->radius = radius;
    this->x = x;
    this->y = y;
    this->res = res;
}

int Circle::getVerticesArraySize(){
    return (res+1)*3;
}

int Circle::getIndicesArraySize(){
    return res*3;
}

void Circle::generateVertices(){
    // the first vertex is the center of the circle
    vertices.push_back(x);
    vertices.push_back(y);
    vertices.push_back(0.0f); // since we're working with 2d, Z value is always zero

    for (size_t i = 0; i < res; i++)
    {
        // calculate the next vertex with trigonometry
        GLfloat angle = 2.0f * 3.14159265359 * (static_cast<float>(i) / res);
        GLfloat xVertex = x + cos(angle) * radius;
        GLfloat yVertex = y + sin(angle) * radius;
        // save the vertex, it's i+1 because index 0 is already used by the center point
        vertices.push_back(xVertex);
        vertices.push_back(yVertex);
        vertices.push_back(0.0f); // since we're working with 2d, Z value is always zero
        
        // make the indices, look at sketch.jpg for uhh some kinda explanation lol
        indices.push_back(0);       // indice a
        indices.push_back(i + 1); // indice b
        indices.push_back(i + 2); // indice c
    }
    indices.back() = 1; // connects the last triangle to the first generated vertex
}