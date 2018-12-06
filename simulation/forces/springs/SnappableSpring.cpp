//
// Created by Petr Flajsingr on 2018-12-02.
//

#include <iostream>
#include <StdoutLogger.h>
#include "SnappableSpring.h"

PGRsim::SnappableSpring::SnappableSpring(float stiffness,
                               float damping,
                                       PGRsim::SimObject *simulatedObjectA,
                                       PGRsim::SimObject *simulatedObjectB,
                               float snapLimit) : Spring(stiffness, damping, simulatedObjectA, simulatedObjectB),
                                                  snapLimit(snapLimit) {}

void PGRsim::SnappableSpring::applyForce(SimObject &object) {
  applyForce();
}
void PGRsim::SnappableSpring::applyForce() {
  if (snapped) {
    return;
  }
  Spring::applyForce();

  // check for force limit
  if (abs(glm::length(force)) > snapLimit) {
    snapped = true;
  }
}
