//
// Created by Petr on 29.11.2018.
//

#ifndef PGR_PROJECT_EULERINTEGRATOR_H
#define PGR_PROJECT_EULERINTEGRATOR_H


#include "../base/Integrator.h"

class EulerIntegrator : public Integrator {
private:
protected:
public:
    EulerIntegrator(float timeStep);

    void integrate(glm::vec3 acceleration, SimulatedObject *object) override;

};


#endif //PGR_PROJECT_EULERINTEGRATOR_H
