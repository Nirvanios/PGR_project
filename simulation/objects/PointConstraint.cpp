//
// Created by Petr Flajsingr on 2018-12-01.
//

#include "PointConstraint.h"
PointConstraint::PointConstraint(const glm::vec3 &position, SimObject *object) : position(position), object(object) {}

void PointConstraint::satisfyConstraint() {
  object->setCurrentPosition(position);
}
