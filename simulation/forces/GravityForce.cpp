//
// Created by Petr on 28.11.2018.
//

#include "GravityForce.h"

void PGRsim::GravityForce::applyForce(SimObject &object) {
  object.setResultantForce(object.getResultantForce() + acceleration * object.getMass());
}

PGRsim::GravityForce::GravityForce() : acceleration(glm::vec3(0, -9.8f, 0)) {}

void PGRsim::GravityForce::disable() {
  acceleration = glm::vec3(0, 0, 0);
}
void PGRsim::GravityForce::enable() {
  acceleration = glm::vec3(0, -9.8f, 0);
}
