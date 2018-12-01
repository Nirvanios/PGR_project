//
// Created by Petr on 29.11.2018.
//

#ifndef PGR_PROJECT_SIMULATION_H
#define PGR_PROJECT_SIMULATION_H

#include <vector>
#include "base/SimulatedObject.h"
#include "base/ForceGenerator.h"
#include "forces/Spring.h"
#include "base/Integrator.h"
#include "integrators/EulerIntegrator.h"
#include "objects/Constraint.h"

class Simulation {
private:
protected:
    std::vector<SimulatedObject*> objects;
    std::vector<ForceGenerator*> forces;
    std::vector<Spring*> springs;
    std::vector<Constraint*> constraints;
    int constraintIterations;

    Integrator* integrator;
public:
    Simulation();

    void addSpring(float stiffness, float damping, SimulatedObject* objectA, SimulatedObject* objectB);

    void addObject(SimulatedObject* object);

    void addGlobalForce(ForceGenerator* force);

    void addConstraint(Constraint* constraint);

    void setConstraintIterations(int value) {
      constraintIterations = value;
    }

    int getConstraintIterations() {
      return constraintIterations;
    }

    virtual void update(SimulationTime time);
};


#endif //PGR_PROJECT_SIMULATION_H
