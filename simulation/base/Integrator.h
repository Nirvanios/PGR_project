//
// Created by Petr on 29.11.2018.
//

#ifndef PGR_PROJECT_INTEGRATOR_H
#define PGR_PROJECT_INTEGRATOR_H

#include "SimulatedObject.h"

class Integrator {
private:
protected:
    float timeStep;
public:
    Integrator(float timeStep) : timeStep(timeStep) {}

    void setTimeStep(float step) {
        this ->timeStep = step;
    }

    float getTimeStep() {
        return timeStep;
    }

    virtual void integrate(glm::vec3 acceleration, SimulatedObject* object)=0;
};

#endif //PGR_PROJECT_INTEGRATOR_H