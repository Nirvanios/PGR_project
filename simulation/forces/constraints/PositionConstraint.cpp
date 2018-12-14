//
// Created by Petr Flajsingr on 2018-12-01.
//

#include "PositionConstraint.h"
PGRsim::PositionConstraint::PositionConstraint(const glm::vec3 &position, PGRsim::SimObject *object)
    : position(position), object(object) {}

void PGRsim::PositionConstraint::satisfyConstraint() {
  if (!isEnabled()) {
    return;
  }
  object->setCurrentPosition(position);
}
