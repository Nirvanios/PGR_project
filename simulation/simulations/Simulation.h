//
// Created by Petr on 29.11.2018.
//

#ifndef PGR_PROJECT_SIMULATION_H
#define PGR_PROJECT_SIMULATION_H

#include <vector>
#include "SimObject.h"
#include "ForceGenerator.h"
#include "Spring.h"
#include "Integrator.h"
#include "EulerIntegrator.h"
#include "VerletIntegrator.h"
#include "Constraint.h"

class Simulation {
private:
protected:
    std::vector<SimObject*> objects;
    std::vector<ForceGenerator*> forces;
    std::vector<Spring*> springs;
    std::vector<Constraint*> constraints;
    int constraintIterations;

    Integrator* integrator;
public:
    Simulation();

    void addSpring(float stiffness, float damping, SimObject* objectA, SimObject* objectB);

    void addObject(SimObject* object);

    const std::vector<SimObject*>& getObjects() {
      return objects;
    }

    void addGlobalForce(ForceGenerator* force);

    void addConstraint(Constraint* constraint);

    void setConstraintIterations(int value) {
      constraintIterations = value;
    }

    int getConstraintIterations() {
      return constraintIterations;
    }

    void setIntegrator(Integrator* integrator) {
      this->integrator = integrator;
    }

    virtual void update(SimTime time);
};


#endif //PGR_PROJECT_SIMULATION_H
