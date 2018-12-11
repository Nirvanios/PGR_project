//
// Created by Petr Flajsingr on 2018-12-01.
//

#include "PointConstraint.h"
PGRsim::PointConstraint::PointConstraint(const glm::vec3 &position, PGRsim::SimObject *object)
    : position(position), object(object) {}

void PGRsim::PointConstraint::satisfyConstraint() {
  if (!isEnabled()) {
    return;
  }
  object->setCurrentPosition(position);
}
