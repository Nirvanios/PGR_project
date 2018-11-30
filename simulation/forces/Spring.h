//
// Created by Petr on 29.11.2018.
//

#ifndef PGR_PROJECT_SPRING_H
#define PGR_PROJECT_SPRING_H

#include <glm/geometric.hpp>
#include "../base/ForceGenerator.h"

class Spring : public ForceGenerator {
private:
    float stiffness;
    float damping;
    float restLength;

    SimulatedObject* simulatedObjectA;
    SimulatedObject* simulatedObjectB;

    glm::vec3 direction;
    glm::vec3 force;
    float currentLength;
protected:
public:
    Spring(float stiffness, float damping, SimulatedObject *simulatedObjectA,
           SimulatedObject *simulatedObjectB);

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

    void setSimulatedObjectA(SimulatedObject* object) {
        this->simulatedObjectA = object;
    }

    float getSimulatedObjectA() {
        return stiffness;
    }

    void setSimulatedObjectB(SimulatedObject* object) {
        this->simulatedObjectB = object;
    }

    float getSimulatedObjectB() {
        return stiffness;
    }

    void applyForce(SimulatedObject *object) override;
};


#endif //PGR_PROJECT_SPRING_H
