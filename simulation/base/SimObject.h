//
// Created by Petr on 27.11.2018.
//

#ifndef PGR_PROJECT_SIMULATEDOBJECT_H
#define PGR_PROJECT_SIMULATEDOBJECT_H

#include <GL/glew.h>
#ifdef _WIN32
#include <GL/gl.h>
#elif __APPLE__
#include <Opengl/gl.h>
#endif
#include <glm/vec3.hpp>
#include "common.h"

enum SimObjectType {
    Passive, Active
};

class SimObject {
private:
    float mass;
    SimObjectType objectType;

protected:
    glm::vec3 currentPosition;
    glm::vec3 previousPosition;
    glm::vec3 velocity;
    glm::vec3 resultantForce;
public:
    SimObject(float mass, SimObjectType objectType) : mass(mass), objectType(objectType) {
        currentPosition = glm::vec3(0, 0, 0);
        previousPosition = currentPosition;
        velocity = glm::vec3(0, 0, 0);
        resultantForce = glm::vec3(0, 0, 0);
    }

    void setMass(float newMass) {
        mass = newMass;
    }

    float getMass() {
        return mass;
    }

    void setSimulatedObjectType(SimObjectType type) {
        this->objectType = type;
    }

    SimObjectType getSimulatedObjectType() {
        return objectType;
    }

    void setCurrentPosition(glm::vec3 position) {
        this->currentPosition = position;
    }

    glm::vec3 getCurrectPosition() {
        return currentPosition;
    }

    void setPreviousPosition(glm::vec3 position) {
        this->previousPosition = position;
    }

    glm::vec3 getPreviousPosition() {
        return previousPosition;
    }

    void setVelocity(glm::vec3 velocity) {
        this->velocity = velocity;
    }

    glm::vec3 getVelocity() {
        return velocity;
    }

    void setResultantForce(glm::vec3 force) {
        this->resultantForce = force;
    }

    glm::vec3 getResultantForce() {
        return resultantForce;
    }

    void resetForces() {
        resultantForce = glm::vec3(0, 0, 0);
    }

    virtual void update(SimTime time) = 0;
};


#endif //PGR_PROJECT_SIMULATEDOBJECT_H
