//
// Created by Petr Flajsingr on 2018-12-01.
//

#include "ConstantForce.h"
void ConstantForce::applyForce(SimulatedObject *object) {
  object->setResultantForce(object->getResultantForce() + force);
}

ConstantForce::ConstantForce(const glm::vec3 &force) : force(force) {}
