//
// Created by Petr on 28.11.2018.
//

#ifndef PGR_PROJECT_GRAVITYFORCE_H
#define PGR_PROJECT_GRAVITYFORCE_H

#include <glm/glm.hpp>
#include <glm/gtx/scalar_multiplication.hpp>
#include "ForceGenerator.h"

namespace PGRsim {

/**
 * Gravity force applied to the entire are based on real gravity.
 *
 * Acceleration: 0, -9.8f, 0
 */
class GravityForce final : public ForceGenerator {
 private:
  glm::vec3 acceleration;
 public:
  GravityForce();

  void applyForce(SimObject *object) override;

  glm::vec3 getAcceleration() {
    return acceleration;
  }

  void disable();

  void enable();
};
}

#endif //PGR_PROJECT_GRAVITYFORCE_H
