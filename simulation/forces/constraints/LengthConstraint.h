//
// Created by Petr Flajsingr on 2018-12-01.
//

#ifndef PGR_PROJECT_LENGTHCONSTRAINT_H
#define PGR_PROJECT_LENGTHCONSTRAINT_H

#include "Constraint.h"
#include "SimpleObject.h"

namespace PGRsim {

/**
 * Maintains distance between two objects.
 *
 * @author Petr Flajšingr
 */
class LengthConstraint : public Constraint {
 private:
  SimObject *objectA;
  SimObject *objectB;

  float length;

  glm::vec3 direction;
  glm::vec3 moveVector;
  float currentLength;
 protected:
 public:
  /**
   *
   * @param objectA
   * @param objectB
   * @param length desired length
   */
  LengthConstraint(SimObject *objectA, SimObject *objectB, float length);

  void satisfyConstraint() override;

  void setSimulatedObjectA(SimObject *object);

  void setSimulatedObjectB(SimObject *object);

  SimObject *getObjectA() const;
  SimObject *getObjectB() const;
};
}

#endif //PGR_PROJECT_LENGTHCONSTRAINT_H
