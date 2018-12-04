//
// Created by Petr on 29.11.2018.
//

#ifndef PGR_PROJECT_SPRING_H
#define PGR_PROJECT_SPRING_H

#include <glm/geometric.hpp>
#include "ForceGenerator.h"

namespace PGRsim {

/**
 * Force connecting two objects together.
 *
 * The spring can be configured via its stiffness and damping parameters.
 *
 * Length is calculated at the time of creation of the object as a distance between connected objects.
 */
class Spring : public ForceGenerator {
 protected:
  float stiffness;
  float damping;
  float restLength;
  glm::vec3 direction;
  glm::vec3 force;

  float currentLength;

  SimObject *simulatedObjectA;
  SimObject *simulatedObjectB;
 public:
  Spring(float stiffness, float damping, SimObject *simulatedObjectA,
         SimObject *simulatedObjectB);

  void setStiffness(float stiffness) {
    this->stiffness = stiffness;
  }

  float getStiffness() {
    return stiffness;
  }

  void setDamping(float damping) {
    this->damping = damping;
  }

  float getDamping() {
    return stiffness;
  }

  void setSimulatedObjectA(SimObject *object) {
    this->simulatedObjectA = object;
  }

  float getSimulatedObjectA() {
    return stiffness;
  }

  void setSimulatedObjectB(SimObject *object) {
    this->simulatedObjectB = object;
  }

  float getSimulatedObjectB() {
    return stiffness;
  }

  void applyForce(SimObject &object) override;

  virtual void applyForce();
};
}

#endif //PGR_PROJECT_SPRING_H
