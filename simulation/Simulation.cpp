//
// Created by Petr on 29.11.2018.
//

#include "Simulation.h"

Simulation::Simulation() {
    integrator = new EulerIntegrator(1.0f / 60.0f);
}

void Simulation::addSpring(float stiffness, float damping, float restLength, SimulatedObject* objectA, SimulatedObject* objectB) {
    springs.emplace_back(new Spring(stiffness, damping, restLength, objectA, objectB));
}

void Simulation::addObject(SimulatedObject *object)  {
    objects.emplace_back(object);
}

void Simulation::addGlobalForce(ForceGenerator *force) {
    forces.emplace_back(force);
}

void Simulation::update(SimulationTime time) {
    for (auto spring : springs) {
        spring->applyForce(nullptr);
    }

    glm::vec3 acceleration;
    for (auto object : objects) {
        if (object->getSimulatedObjectType() == Active) {
            acceleration = object->getResultantForce() / object->getMass();

            integrator->integrate(acceleration, object);
        }

        object->update(time);

        if (object->getSimulatedObjectType() == Active) {
            object->resetForces();
        }
    }
}
