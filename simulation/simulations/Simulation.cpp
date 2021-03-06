//
// Created by Petr on 29.11.2018.
//

#include <thread>
#include "Simulation.h"

PGRsim::Simulation::Simulation() {
  integrator = new VerletIntegrator(1.0f / 60.0f);
}

void PGRsim::Simulation::addSpring(float stiffness, float damping, SimObject *objectA, SimObject *objectB) {
  springs.emplace_back(new Spring(stiffness, damping, objectA, objectB));
}

void PGRsim::Simulation::addObject(SimObject *object) {
  objects.emplace_back(object);
}

void PGRsim::Simulation::addForce(ForceBase *force) {
  forces.emplace_back(force);
}

void PGRsim::Simulation::update(SimTime time) {
  for (auto spring : springs) {
    spring->applyForce();
  }

  glm::vec3 acceleration;
  for (auto object : objects) {
    if (object->getSimulatedObjectType() == Active || object->getSimulatedObjectType() == Shape) {
      for (auto forceGenerator : forces) {
        forceGenerator->applyForce(*object);
      }
    }
  }

  for (auto object : objects) {
    if (object->getSimulatedObjectType() == Active || object->getSimulatedObjectType() == Shape) {
      acceleration = object->getResultantForce() / object->getMass();

      integrator->integrate(acceleration, *object);
    }
  }

  std::thread thread(
      &Simulation::threadConstraints,
      this,
      0,
      constraints.size() / 2);

  threadConstraints(static_cast<int>(constraints.size() / 2), static_cast<int>(constraints.size()));

  thread.join();

  for (auto object : objects) {
    object->update(time);

    if (object->getSimulatedObjectType() == Active || object->getSimulatedObjectType() == Shape) {
      object->resetForces();
    }
  }
}

void PGRsim::Simulation::addConstraint(Constraint *constraint) {
  constraints.emplace_back(constraint);
}

void PGRsim::Simulation::addSpring(Spring *spring) {
  springs.emplace_back(spring);
}

void PGRsim::Simulation::threadConstraints(int start, int end) {
  for (int i = 0; i < constraintIterations; i++) {
    for (int j = start; j < end; j++) {
      constraints[j]->satisfyConstraint();
    }
  }
}

const std::vector<PGRsim::SimObject *> &PGRsim::Simulation::getObjects() {
  return objects;
}

void PGRsim::Simulation::setConstraintIterations(int value) {
  constraintIterations = value;
}

void PGRsim::Simulation::setIntegrator(PGRsim::Integrator *integrator) {
  this->integrator = integrator;
}

PGRsim::Simulation::~Simulation() {
  for (auto it : objects) {
    delete it;
  }
  for (auto it : springs) {
    delete it;
  }
  for (auto it : constraints) {
    delete it;
  }
  for (auto it : forces) {
    delete it;
  }

  delete integrator;

}
