//
// Created by Petr on 28.11.2018.
//

#ifndef PGR_PROJECT_CONSTRAINT_H
#define PGR_PROJECT_CONSTRAINT_H


namespace PGRsim {
class Constraint {
 public:
  virtual void satisfyConstraint() = 0;
};
}

#endif //PGR_PROJECT_CONSTRAINT_H
