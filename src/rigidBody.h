#pragma once
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <shape.h>

using namespace std;

class RigidBody{
  public:
    glm::vec2 position;
    glm::vec2 velocity;
    float mass;
    float restitution;    // how bouncy it is

    std::unique_ptr<Shape> shape;
};