//
// Created by Petr on 28.11.2018.
//

#ifndef PGR_PROJECT_GRAVITYFORCE_H
#define PGR_PROJECT_GRAVITYFORCE_H

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/scalar_multiplication.hpp>
#include "ForceGenerator.h"

class GravityForce : public ForceGenerator {
private:
    glm::vec3 acceleration;
public:
    GravityForce();

    void applyForce(SimObject* object) override;

    glm::vec3 getAcceleration() {
        return acceleration;
    }
};


#endif //PGR_PROJECT_GRAVITYFORCE_H
