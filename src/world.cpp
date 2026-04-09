#include <world.h>
#include <rigidBody.h>
#include <circle.h>
#include <shape.h>

void World::addCircle(float radius, float x, float y, int res,float width, float height, glm::vec2 velocity){
    auto body = std::make_unique<RigidBody>();
    body->position = {x, y};
    body->mass = 1.0f;
    body->restitution = 0.7f;
    body->velocity = velocity;
    body->shape = std::make_unique<Circle>(radius, res);
    body->shape->setProjection(width, height);
    bodies.push_back(std::move(body));
}

void World::update(float dt){
    // this is where things like gravity, collision, world borders and things happens
    for(auto&body : bodies){
        body->velocity.y += this->gravity;
        body->position += body->velocity;
    }
}

void World::render(){
    // draw the ball
    for (auto&body : bodies){
        body->shape->draw(body->position);
    }
}

void World::setProjection(float width, float height){
    for(auto& body : bodies){
        body->shape->setProjection(width, height);
    }
}