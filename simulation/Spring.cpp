//
// Created by Petr on 29.11.2018.
//

#include "Spring.h"

Spring::Spring(float stiffness, float damping, float restLength, SimulatedObject *simulatedObjectA,
               SimulatedObject *simulatedObjectB) : stiffness(stiffness), damping(damping), restLength(restLength),
                                                    simulatedObjectA(simulatedObjectA),
                                                    simulatedObjectB(simulatedObjectB) {}

void Spring::applyForce(SimulatedObject *object) {
    direction = simulatedObjectA->getCurrectPosition() - simulatedObjectB->getCurrectPosition();

    if (direction != glm::vec3(0, 0, 0)) {
        currentLength = glm::length(direction);
        direction = glm::normalize(direction);

        force = -stiffness * ((currentLength - restLength) * direction);
        force += damping * glm::dot(simulatedObjectA->getVelocity() - simulatedObjectB->getVelocity(), direction) * direction;

        simulatedObjectA->setResultantForce(simulatedObjectA->getResultantForce() + force);
        simulatedObjectB->setResultantForce(simulatedObjectB->getResultantForce() - force);
    }
}
