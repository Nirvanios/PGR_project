//
// Created by Petr on 29.11.2018.
//

#include "Spring.h"

PGRsim::Spring::Spring(float stiffness, float damping, SimObject *simulatedObjectA,
                       SimObject *simulatedObjectB) : stiffness(stiffness), damping(damping),
                                                      simulatedObjectA(simulatedObjectA),
                                                      simulatedObjectB(simulatedObjectB) {
  restLength = glm::length(simulatedObjectA->getCurrectPosition() - simulatedObjectB->getCurrectPosition());
  currentLength = restLength;
}

void PGRsim::Spring::applyForce(SimObject &object) {
  applyForce();
}
void PGRsim::Spring::applyForce() {
  direction = simulatedObjectA->getCurrectPosition() - simulatedObjectB->getCurrectPosition();

  if (direction != glm::vec3(0, 0, 0)) {
    currentLength = glm::length(direction);
    direction = glm::normalize(direction);

    force = -stiffness * ((currentLength - restLength) * direction);
    force +=
        -damping * glm::dot(simulatedObjectA->getVelocity() - simulatedObjectB->getVelocity(), direction) * direction;

    simulatedObjectA->setResultantForce(simulatedObjectA->getResultantForce() + force);
    simulatedObjectB->setResultantForce(simulatedObjectB->getResultantForce() - force);
  }
}
