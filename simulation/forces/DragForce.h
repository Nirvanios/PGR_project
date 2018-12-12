//
// Created by Petr on 29.11.2018.
//

#ifndef PGR_PROJECT_DRAGFORCE_H
#define PGR_PROJECT_DRAGFORCE_H

#include "ForceBase.h"

namespace PGRsim {

/**
 * Drag force of an environment. Applied to the entire area.
 *
 * @author Petr Flajšingr
 */
class DragForce : public ForceBase {
 private:
  float dragCoefficient = 0.0f;

 public:
  float getDragCoefficient() {
    return dragCoefficient;
  }

  void setDragCoefficient(float coefficient) {
    this->dragCoefficient = coefficient;
  }

  void applyForce(SimObject &object) override;
};
}


#endif //PGR_PROJECT_DRAGFORCE_H
