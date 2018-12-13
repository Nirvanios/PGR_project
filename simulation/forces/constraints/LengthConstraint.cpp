//
// Created by Petr Flajsingr on 2018-12-01.
//

#include <glm/glm.hpp>
#include "LengthConstraint.h"

PGRsim::LengthConstraint::LengthConstraint(PGRsim::SimObject *objectA, PGRsim::SimObject *objectB, float length)
    : objectA(objectA), objectB(objectB), length(length), currentLength(length) {}

void PGRsim::LengthConstraint::satisfyConstraint() {
  if (!isEnabled()) {
    return;
  }
  direction = objectB->getCurrectPosition() - objectA->getCurrectPosition();

  currentLength = glm::length(direction);

  if (direction != glm::vec3(0, 0, 0)) {
    direction = glm::normalize(direction);

    moveVector = 0.5f * (currentLength - length) * direction;
    objectA->setCurrentPosition(objectA->getCurrectPosition() + moveVector);
    objectB->setCurrentPosition(objectB->getCurrectPosition() - moveVector);
  }
}

void PGRsim::LengthConstraint::setSimulatedObjectA(PGRsim::SimObject *object) {
  objectA = object;
}

void PGRsim::LengthConstraint::setSimulatedObjectB(PGRsim::SimObject *object) {
  objectB = object;
}
PGRsim::SimObject *PGRsim::LengthConstraint::getObjectA() const {
  return objectA;
}
PGRsim::SimObject *PGRsim::LengthConstraint::getObjectB() const {
  return objectB;
}

