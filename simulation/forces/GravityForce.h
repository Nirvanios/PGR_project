//
// Created by Petr on 28.11.2018.
//

#ifndef PGR_PROJECT_GRAVITYFORCE_H
#define PGR_PROJECT_GRAVITYFORCE_H


#include "../base/ForceGenerator.h"

class GravityForce : public ForceGenerator {
private:
    glm::vec3 acceleration;
public:
    GravityForce();

    void applyForce(SimulatedObject* object) override;

    glm::vec3 getAcceleration() {
        return acceleration;
    }
};


#endif //PGR_PROJECT_GRAVITYFORCE_H
