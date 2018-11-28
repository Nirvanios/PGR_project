//
// Created by Petr on 27.11.2018.
//

#ifndef PGR_PROJECT_SIMULATEDOBJECT_H
#define PGR_PROJECT_SIMULATEDOBJECT_H

#include <GL/gl.h>
#include <GL/glew.h>
#include <glm/vec3.hpp>

enum SimulatedObjectType {
    Passive, Active
};

class SimulatedObject {
private:
    float mass;
    SimulatedObjectType objectType;

protected:
    glm::vec3 currentPosition;
    glm::vec3 previousPosition;
    glm::vec3 velocity;
public:

    void setMass(float newMass) {
        mass = newMass;
    }

    float getMass() {
        return mass;
    }
};


#endif //PGR_PROJECT_SIMULATEDOBJECT_H
