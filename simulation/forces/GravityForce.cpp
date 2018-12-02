//
// Created by Petr on 28.11.2018.
//

#include "GravityForce.h"

void GravityForce::applyForce(SimObject* object) {
    object->setResultantForce(object->getResultantForce() + acceleration * object->getMass());
}

GravityForce::GravityForce() : acceleration(glm::vec3(0, -9.8f, 0)) {}

void GravityForce::disable() {
    acceleration = glm::vec3(0, 0, 0);
}
void GravityForce::enable() {
    acceleration = glm::vec3(0, -9.8f, 0);
}
