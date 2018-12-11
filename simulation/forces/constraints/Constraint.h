//
// Created by Petr on 28.11.2018.
//

#ifndef PGR_PROJECT_CONSTRAINT_H
#define PGR_PROJECT_CONSTRAINT_H


namespace PGRsim {

/**
 * Interface for constraints that are checked at the end of each time step.
 *
 * @author Petr Flajšingr
 */
class Constraint {
 private:
  bool enabled = true;
 public:
  virtual void satisfyConstraint() = 0;

  /**
   * Enable constraint checking.
   */
  void enable() {
    enabled = true;
  }

  /**
   * Disable constraint checking.
   */
  void disable() {
    enabled = false;
  }

  bool isEnabled() {
    return enabled;
  }
};
}

#endif //PGR_PROJECT_CONSTRAINT_H
