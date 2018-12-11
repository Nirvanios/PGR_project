//
// Created by Petr on 29.11.2018.
//

#ifndef PGR_PROJECT_SIMULATION_H
#define PGR_PROJECT_SIMULATION_H

#include <vector>
#include <SimpleObject.h>
#include <collisions/VertexCollisionChecker.h>
#include "SimObject.h"
#include "ForceGenerator.h"
#include "springs/Spring.h"
#include "Integrator.h"
#include "EulerIntegrator.h"
#include "VerletIntegrator.h"
#include "constraints/Constraint.h"

namespace PGRsim {

/**
 * Base simulation class.
 *
 * Takes care of constraint checking, spring force application and object movement.
 *
 * Also applies forces.
 *
 * Constraint checking is applied in iterations, more iterations mean higher accuracy
 * but worse performance.
 *
 * Subclass this class in order to add more functions.
 *
 * @author Petr Flajšingr
 */
class Simulation {
 protected:
  std::vector<SimObject *> objects;
  std::vector<ForceGenerator *> forces;
  std::vector<Spring *> springs;
  std::vector<Constraint *> constraints;
  int constraintIterations;

  Integrator *integrator;
  Collision::VertexCollisionChecker collisionChecker;

  /**
   * Constraint checking in a thread.
   * @param start start index
   * @param end end index
   */
  void threadConstraints(int start, int end);
 public:
  Simulation();

  void addSpring(float stiffness, float damping, SimObject *objectA, SimObject *objectB);

  void addSpring(Spring *spring);

  virtual void addObject(SimObject *object);

  const std::vector<SimObject *> &getObjects() {
    return objects;
  }

  void addGlobalForce(ForceGenerator *force);

  void addConstraint(Constraint *constraint);

  void setConstraintIterations(int value) {
    constraintIterations = value;
  }

  int getConstraintIterations() {
    return constraintIterations;
  }

  void setIntegrator(Integrator *integrator) {
    this->integrator = integrator;
  }

  virtual void update(SimTime time);
};
}

#endif //PGR_PROJECT_SIMULATION_H
