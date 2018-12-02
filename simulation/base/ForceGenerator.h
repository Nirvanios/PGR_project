//
// Created by Petr on 28.11.2018.
//

#ifndef PGR_PROJECT_FORCEGENERATOR_H
#define PGR_PROJECT_FORCEGENERATOR_H


#include "SimObject.h"

class ForceGenerator {
private:
protected:
public:
    virtual void applyForce(SimObject* object) = 0;
};


#endif //PGR_PROJECT_FORCEGENERATOR_H
