//
// Created by Petr on 29.11.2018.
//

#ifndef PGR_PROJECT_INTEGRATOR_H
#define PGR_PROJECT_INTEGRATOR_H

#include "SimObject.h"

namespace PGRsim {

/**
 * Interface for an integrator applying changes to simulated objects.
 */
class Integrator {
 private:
 protected:
  float timeStep;
 public:
  Integrator(float timeStep) : timeStep(timeStep) {}

  void setTimeStep(float step) {
    this->timeStep = step;
  }

  float getTimeStep() {
    return timeStep;
  }

  virtual void integrate(glm::vec3 acceleration, SimObject *object) = 0;
};
}

#endif //PGR_PROJECT_INTEGRATOR_H
