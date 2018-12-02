//
// Created by Petr Flajsingr on 2018-12-02.
//

#ifndef PGR_PROJECT_SNAPABLESPRING_H
#define PGR_PROJECT_SNAPABLESPRING_H

#include <Spring.h>
#include <glm/glm.hpp>


class SnapableSpring : public Spring {
 private:
  float snapLimit;

  bool snapped = false;
 protected:
 public:
  SnapableSpring(float stiffness,
                 float damping,
                 SimObject *simulatedObjectA,
                 SimObject *simulatedObjectB,
                 float snapLimit);

  void applyForce(SimObject *object) override;
};

#endif //PGR_PROJECT_SNAPABLESPRING_H
