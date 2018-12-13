//
// Created by Petr on 28.11.2018.
//

#ifndef PGR_PROJECT_FORCEGENERATOR_H
#define PGR_PROJECT_FORCEGENERATOR_H


#include "SimObject.h"

namespace PGRsim {

/**
 * Interface for forces acting in the simulation.
 *
 * @author Petr Flajšingr
 */
class ForceBase {
 public:
  /**
   * Apply effects to a simulated object
   * @param object object to apply force to
   */
  virtual void applyForce(SimObject &object) = 0;

  virtual ~ForceBase() = default;
};
}


#endif //PGR_PROJECT_FORCEGENERATOR_H
