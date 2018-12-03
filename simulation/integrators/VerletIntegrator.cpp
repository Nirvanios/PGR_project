//
// Created by Petr Flajsingr on 2018-12-01.
//

#include "VerletIntegrator.h"
PGRsim::VerletIntegrator::VerletIntegrator(float timeStep) : PGRsim::Integrator(timeStep) {}

void PGRsim::VerletIntegrator::integrate(glm::vec3 acceleration, SimObject *object) {
  newPosition = 2.0f * object->getCurrectPosition() - object->getPreviousPosition()
      + acceleration * timeStep * timeStep;

  object->setPreviousPosition(object->getCurrectPosition());
  object->setCurrentPosition(newPosition);
}
