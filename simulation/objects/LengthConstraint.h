//
// Created by Petr Flajsingr on 2018-12-01.
//

#ifndef PGR_PROJECT_LENGTHCONSTRAINT_H
#define PGR_PROJECT_LENGTHCONSTRAINT_H

#include "Constraint.h"
#include "SimObject.h"

class LengthConstraint : public Constraint {
 private:
  SimObject* objectA;
  SimObject* objectB;

  float length;

  glm::vec3 direction;
  glm::vec3 moveVector;
  float currentLength;
 protected:
 public:
  LengthConstraint(SimObject *objectA, SimObject *objectB, float length);

  void satisfyConstraint() override;
};

#endif //PGR_PROJECT_LENGTHCONSTRAINT_H
