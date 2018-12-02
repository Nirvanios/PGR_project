//
// Created by Petr on 29.11.2018.
//

#include "Simulation.h"

Simulation::Simulation() {
    integrator = new EulerIntegrator(1.0f / 60.0f);
}

void Simulation::addSpring(float stiffness, float damping, SimObject* objectA, SimObject* objectB) {
    springs.emplace_back(new Spring(stiffness, damping, objectA, objectB));
}

void Simulation::addObject(SimObject *object)  {
    objects.emplace_back(object);
}

void Simulation::addGlobalForce(ForceGenerator *force) {
    forces.emplace_back(force);
}

void Simulation::update(SimTime time) {
    for (auto spring : springs) {
        spring->applyForce(nullptr);
    }

    glm::vec3 acceleration;
    for (auto object : objects) {
        if (object->getSimulatedObjectType() == Active) {
            for (auto forceGenerator : forces) {
                forceGenerator->applyForce(object);
            }
        }
    }

    for (auto object : objects) {
        if (object->getSimulatedObjectType() == Active) {
            acceleration = object->getResultantForce() / object->getMass();

            integrator->integrate(acceleration, object);
        }
    }

    for (int i = 0; i < constraintIterations; i++) {
        for (auto constraint : constraints) {
            constraint->satisfyConstraint();
        }
    }


    for (auto object : objects) {
        object->update(time);

        if (object->getSimulatedObjectType() == Active) {
            object->resetForces();
        }
    }
}
void Simulation::addConstraint(Constraint *constraint) {
    constraints.emplace_back(constraint);
}
