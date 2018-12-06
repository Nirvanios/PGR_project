//
// Created by Petr on 28.11.2018.
//

#ifndef PGR_PROJECT_CONSTRAINT_H
#define PGR_PROJECT_CONSTRAINT_H


namespace PGRsim {

enum ConstraintType {
  Point, Length
};

/**
 * Interface for constraints that are checked at the end of each time step.
 */
class Constraint {
 private:
  bool enabled = true;
 public:
  virtual void satisfyConstraint() = 0;

  void enable() {
    enabled = true;
  }

  void disable() {
    enabled = false;
  }

  bool isEnabled() {
    return enabled;
  }
};
}

#endif //PGR_PROJECT_CONSTRAINT_H
