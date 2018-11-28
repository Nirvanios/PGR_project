//
// Created by Petr on 28.11.2018.
//

#include "GravityForce.h"

void GravityForce::applyForce(SimulatedObject* object) {

}

GravityForce::GravityForce() : acceleration(glm::vec3(0, -9.8, 0)) {}
