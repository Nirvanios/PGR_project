//
// Created by Petr on 29.11.2018.
//

#ifndef PGR_PROJECT_SPRING_H
#define PGR_PROJECT_SPRING_H

#include <glm/geometric.hpp>
#include "ForceGenerator.h"

class Spring : public ForceGenerator {
private:
    float stiffness;
    float damping;
    float restLength;

    SimObject* simulatedObjectA;
    SimObject* simulatedObjectB;

    glm::vec3 direction;
    glm::vec3 force;
    float currentLength;
protected:
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

    void setSimulatedObjectA(SimObject* object) {
        this->simulatedObjectA = object;
    }

    float getSimulatedObjectA() {
        return stiffness;
    }

    void setSimulatedObjectB(SimObject* object) {
        this->simulatedObjectB = object;
    }

    float getSimulatedObjectB() {
        return stiffness;
    }

    void applyForce(SimObject *object) override;
};


#endif //PGR_PROJECT_SPRING_H
