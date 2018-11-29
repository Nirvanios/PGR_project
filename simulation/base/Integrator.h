//
// Created by Petr on 29.11.2018.
//

#ifndef PGR_PROJECT_INTEGRATOR_H
#define PGR_PROJECT_INTEGRATOR_H

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
};

#endif //PGR_PROJECT_INTEGRATOR_H
