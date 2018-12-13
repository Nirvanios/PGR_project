//
// Created by Petr on 29.11.2018.
//

#ifndef PGR_PROJECT_INTEGRATOR_H
#define PGR_PROJECT_INTEGRATOR_H

#include <iostream>
#include "SimObject.h"

namespace PGRsim {

/**
 * Interface for an integrator applying changes to simulated objects.
 *
 * @author Petr Flajšingr
 */
class Integrator {
 private:
  float timeStep;

 public:
  explicit Integrator(float timeStep) : timeStep(timeStep) {}

  virtual ~Integrator() = default;

  void setTimeStep(float step) {
    this->timeStep = step;
  }

  float getTimeStep() {
    return timeStep;
  }

  virtual void integrate(glm::vec3 acceleration, SimObject &object) = 0;
};
}

#endif //PGR_PROJECT_INTEGRATOR_H
