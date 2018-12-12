//
// Created by Petr on 29.11.2018.
//

#include "EulerIntegrator.h"

void PGRsim::EulerIntegrator::integrate(glm::vec3 acceleration, SimObject &object) {
  object.setCurrentPosition(object.getCurrectPosition() + object.getResultantForce() * getTimeStep());

  object.setResultantForce(object.getResultantForce() + acceleration * getTimeStep());
}

PGRsim::EulerIntegrator::EulerIntegrator(float timeStep) : Integrator(timeStep) {}
