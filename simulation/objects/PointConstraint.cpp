//
// Created by Petr Flajsingr on 2018-12-01.
//

#include "PointConstraint.h"
PointConstraint::PointConstraint(const glm::vec3 &position, SimulatedObject *object) : position(position), object(object) {}

void PointConstraint::satisfyContraint() {
  object->setCurrentPosition(position);
}
