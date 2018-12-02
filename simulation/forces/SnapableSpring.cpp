//
// Created by Petr Flajsingr on 2018-12-02.
//

#include <iostream>
#include "SnapableSpring.h"

SnapableSpring::SnapableSpring(float stiffness,
                               float damping,
                               SimObject *simulatedObjectA,
                               SimObject *simulatedObjectB,
                               float snapLimit) : Spring(stiffness, damping, simulatedObjectA, simulatedObjectB),
                                                  snapLimit(snapLimit) {}
void SnapableSpring::applyForce(SimObject *object) {
  if (snapped) {
    return;
  }
  Spring::applyForce(object);

  if (abs(force[0]) > snapLimit || abs(force[1]) > snapLimit || abs(force[2]) > snapLimit) {
    snapped = true;
  }
}
