#pragma once
#include <vector>
#include <stdlib.h>
#include <memory>
#include <rigidBody.h>

class World{
    public:
    std::vector<std::unique_ptr<RigidBody>> bodies;
    void addCircle(float radius, float x, float y, int res,float width, float height);
    void update(float dt);
    void render();
    void setProjection(float width, float height);
};