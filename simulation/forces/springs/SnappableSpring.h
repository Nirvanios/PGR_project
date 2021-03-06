//
// Created by Petr Flajsingr on 2018-12-02.
//

#ifndef PGR_PROJECT_SNAPABLESPRING_H
#define PGR_PROJECT_SNAPABLESPRING_H

#include <springs/Spring.h>
#include <glm/glm.hpp>

namespace PGRsim {

/**
 * In addition to the properties of Spring, this class provides an option to quit applying force
 * when a force above set value is applied by the string.
 *
 * @see PGRsim::Spring
 *
 * @author Petr Flajšingr
 */
class SnappableSpring : public Spring {
  friend class SnappableSpringGroup;
 private:
  float snapLimit;

  bool snapped = false;
 protected:
 public:
  /**
   *
   * @param stiffness
   * @param damping
   * @param simulatedObjectA
   * @param simulatedObjectB
   * @param snapLimit value at which the spring snaps
   */
  SnappableSpring(float stiffness,
                  float damping,
                  SimObject *simulatedObjectA,
                  SimObject *simulatedObjectB,
                  float snapLimit);

  void applyForce(SimObject &object) override;

  void applyForce() override;

  bool isSnapped() {
    return snapped;
  }
};
}

#endif //PGR_PROJECT_SNAPABLESPRING_H
