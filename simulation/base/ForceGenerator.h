//
// Created by Petr on 28.11.2018.
//

#ifndef PGR_PROJECT_FORCEGENERATOR_H
#define PGR_PROJECT_FORCEGENERATOR_H


#include "SimpleObject.h"

namespace PGRsim {

/**
 * Interface for forces acting in the simulation.
 */
class ForceGenerator {
 private:
 protected:
 public:
  /**
   * Apply effects to a simulated object
   * @param object
   */
  virtual void applyForce(SimObject *object) = 0;
};
}


#endif //PGR_PROJECT_FORCEGENERATOR_H
