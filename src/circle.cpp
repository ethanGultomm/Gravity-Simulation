#include "circle.h"

Circle::Circle(GLfloat radius, GLfloat x, GLfloat y, int res){
    this->radius = radius;
    this->x = x;
    this->y = y;
    this->res = res;

    // configure the shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    modelLoc = glGetUniformLocation(shaderProgram, "model");
    projLoc = glGetUniformLocation(shaderProgram, "projection");

    init();
}

Circle::~Circle(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
}

void Circle::init(){
    generateVertices();

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

// all vertices are generated with 0,0 as the center.
void Circle::generateVertices(){
    vertices.clear();
    indices.clear();
    // the first vertex is the center of the circle
    vertices.push_back(0.0f);
    vertices.push_back(0.0f);
    vertices.push_back(0.0f);

    for (size_t i = 0; i < res; i++)
    {
        // calculate the next vertex with trigonometry
        GLfloat angle = 2.0f * 3.14159265359 * (static_cast<float>(i) / res);
        GLfloat xVertex = cos(angle) * radius;
        GLfloat yVertex = sin(angle) * radius;
        // save the vertex
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

void Circle::draw(GLfloat newX, GLfloat newY){
    // set the new center
    x = newX;
    y = newY;
    glUseProgram(shaderProgram);

    // create model matrix (move circle)
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0f));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
}

void Circle::setProjection(float width, float height){
    float aspect = width / height;
    glm::mat4 projection = glm::ortho(-aspect, aspect, -1.0f, 1.0f);
    glUseProgram(shaderProgram);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
}