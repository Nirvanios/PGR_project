//
// Created by Petr on 28.11.2018.
//

#ifndef PGR_PROJECT_GRAVITYFORCE_H
#define PGR_PROJECT_GRAVITYFORCE_H


#include "base/ForceGenerator.h"

class GravityForce : public ForceGenerator {
public:
    void applyForce(SimulatedObject* object) override;

};


#endif //PGR_PROJECT_GRAVITYFORCE_H
