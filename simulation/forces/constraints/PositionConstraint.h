//
// Created by Petr Flajsingr on 2018-12-01.
//

#ifndef PGR_PROJECT_POINTCONSTRAINT_H
#define PGR_PROJECT_POINTCONSTRAINT_H

#include <glm/glm.hpp>
#include "Constraint.h"
#include "SimpleObject.h"

namespace PGRsim {

/**
 * Maintains location of a chosen object.
 *
 * @author Petr Flajšingr
 */
class PositionConstraint : public Constraint {
 private:
  glm::vec3 position;
  SimObject *object;
 protected:
 public:
  /**
   *
   * @param position desired location
   * @param object
   */
  PositionConstraint(const glm::vec3 &position, SimObject *object);

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
