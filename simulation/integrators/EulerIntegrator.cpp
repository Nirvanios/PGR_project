//
// Created by Petr on 29.11.2018.
//

#include "EulerIntegrator.h"

void EulerIntegrator::integrate(glm::vec3 acceleration, SimulatedObject *object) {
    object->setCurrentPosition(object->getCurrectPosition() + object->getVelocity() * timeStep);

    object->setVelocity(object->getVelocity() + acceleration * timeStep);
}
