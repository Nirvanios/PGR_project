//
// Created by Petr Flajsingr on 2018-12-01.
//

#ifndef PGR_PROJECT_VERLETINTEGRATOR_H
#define PGR_PROJECT_VERLETINTEGRATOR_H

#include "Integrator.h"

namespace PGRsim {

/**
 * Main integrator for simulations.
 *
 * @author Petr Flajšingr
 */
class VerletIntegrator : public Integrator {
 private:
  glm::vec3 newPosition;
 protected:
 public:
  explicit VerletIntegrator(float timeStep);

  void integrate(glm::vec3 acceleration, SimObject &object) override;
};
}

#endif //PGR_PROJECT_VERLETINTEGRATOR_H
