//
// Created by Petr on 29.11.2018.
//

#ifndef PGR_PROJECT_DRAGFORCE_H
#define PGR_PROJECT_DRAGFORCE_H


#include "ForceGenerator.h"

class DragForce : public ForceGenerator {
private:
    float dragCoefficient;
public:
    float getDragCoefficient() {
        return dragCoefficient;
    }

    void setDragCoefficient(float coefficient) {
        this->dragCoefficient = coefficient;
    }

    void applyForce(SimulatedObject *object) override;

};


#endif //PGR_PROJECT_DRAGFORCE_H
