//
// Created by Petr on 28.11.2018.
//

#ifndef PGR_PROJECT_SIMULATEDMODEL_H
#define PGR_PROJECT_SIMULATEDMODEL_H


#include "SimulatedObject.h"

class SimulatedModel: public SimulatedObject {
private:
  GraphicsSimpleObject* model;
public:
    SimulatedModel(float mass, SimulatedObjectType objectType, GraphicsSimpleObject* model);

    void setObjectModel(GraphicsSimpleObject* model) {
        this->model = model;
    }

  GraphicsSimpleObject* getObjectModel() {
        return model;
    }

    void update(SimulationTime time) override;
};


#endif //PGR_PROJECT_SIMULATEDMODEL_H
