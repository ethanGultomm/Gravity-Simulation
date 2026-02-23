#pragma once
#include <glm/gtc/type_ptr.hpp>

class Shape{
    public:
    virtual ~Shape() = default;
    virtual void draw(const glm::vec2& position) = 0;
    virtual void setProjection(float width, float height) = 0;
};