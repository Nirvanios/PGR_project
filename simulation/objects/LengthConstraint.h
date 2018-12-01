//
// Created by Petr Flajsingr on 2018-12-01.
//

#ifndef PGR_PROJECT_LENGTHCONSTRAINT_H
#define PGR_PROJECT_LENGTHCONSTRAINT_H

#include "Constraint.h"
#include "../base/SimulatedObject.h"

class LengthConstraint : public Constraint {
 private:
  SimulatedObject* objectA;
  SimulatedObject* objectB;

  float length;

  glm::vec3 direction;
  glm::vec3 moveVector;
  float currentLength;
 protected:
 public:
  LengthConstraint(SimulatedObject *objectA, SimulatedObject *objectB, float length);

  void satisfyContraint() override;
};

#endif //PGR_PROJECT_LENGTHCONSTRAINT_H
