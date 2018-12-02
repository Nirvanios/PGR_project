//
// Created by Petr on 29.11.2018.
//

#ifndef PGR_PROJECT_EULERINTEGRATOR_H
#define PGR_PROJECT_EULERINTEGRATOR_H


#include "Integrator.h"

class EulerIntegrator : public Integrator {
private:
protected:
public:
    EulerIntegrator(float timeStep);

    void integrate(glm::vec3 acceleration, SimObject *object) override;

};


#endif //PGR_PROJECT_EULERINTEGRATOR_H
