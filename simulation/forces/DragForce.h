//
// Created by Petr on 29.11.2018.
//

#ifndef PGR_PROJECT_DRAGFORCE_H
#define PGR_PROJECT_DRAGFORCE_H


#include "ForceGenerator.h"

namespace PGRsim {

/**
 * Drag force of an environment. Applied to the entire area.
 */
class DragForce : public ForceGenerator {
 private:
  float dragCoefficient;
 public:
  float getDragCoefficient() {
    return dragCoefficient;
  }

  void setDragCoefficient(float coefficient) {
    this->dragCoefficient = coefficient;
  }

  void applyForce(SimObject *object) override;
};
}


#endif //PGR_PROJECT_DRAGFORCE_H
