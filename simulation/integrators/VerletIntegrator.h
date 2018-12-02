//
// Created by Petr Flajsingr on 2018-12-01.
//

#ifndef PGR_PROJECT_VERLETINTEGRATOR_H
#define PGR_PROJECT_VERLETINTEGRATOR_H

#include "Integrator.h"
class VerletIntegrator : public Integrator {
 private:
  glm::vec3 newPosition;
 protected:
 public:
  VerletIntegrator(float timeStep);

  void integrate(glm::vec3 acceleration, SimObject *object) override;
};

#endif //PGR_PROJECT_VERLETINTEGRATOR_H
