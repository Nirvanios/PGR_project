//
// Created by Petr Flajsingr on 2018-12-01.
//

#ifndef PGR_PROJECT_POINTCONSTRAINT_H
#define PGR_PROJECT_POINTCONSTRAINT_H

#include <glm/glm.hpp>
#include "Constraint.h"
#include "SimObject.h"

namespace PGRsim {

/**
 * Maintains location of a chosen object.
 */
class PointConstraint : public Constraint {
 private:
  glm::vec3 position;
  SimObject *object;
 protected:
 public:
  PointConstraint(const glm::vec3 &position, SimObject *object);

  void setPosition(glm::vec3 pos) {
    this->position = pos;
  }

  glm::vec3 getPosition() {
    return position;
  }

  void satisfyConstraint() override;
};
}

#endif //PGR_PROJECT_POINTCONSTRAINT_H
