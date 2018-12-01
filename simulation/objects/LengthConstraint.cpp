//
// Created by Petr Flajsingr on 2018-12-01.
//

#include <glm/glm.hpp>
#include "LengthConstraint.h"

LengthConstraint::LengthConstraint(SimulatedObject *objectA, SimulatedObject *objectB, float length)
    : objectA(objectA), objectB(objectB), length(length) {}

void LengthConstraint::satisfyContraint() {
  direction = objectB->getCurrectPosition() - objectA->getCurrectPosition();

  currentLength = glm::length(direction);

  if (direction != glm::vec3(0, 0, 0)) {
    direction = glm::normalize(direction);

    moveVector = 0.5f * (currentLength - length) * direction;
    objectA->setCurrentPosition(objectA->getCurrectPosition() + moveVector);
    objectB->setCurrentPosition(objectB->getCurrectPosition() - moveVector);
  }
}

