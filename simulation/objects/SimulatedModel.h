//
// Created by Petr on 28.11.2018.
//

#ifndef PGR_PROJECT_SIMULATEDMODEL_H
#define PGR_PROJECT_SIMULATEDMODEL_H

#include <SimpleGraphicsModel.h>
#include "SimulatedObject.h"

class SimulatedModel: public SimulatedObject {
private:
  SimpleGraphicsModel* model;
public:
    SimulatedModel(float mass, SimulatedObjectType objectType, SimpleGraphicsModel* model);

    void setObjectModel(SimpleGraphicsModel* model) {
        this->model = model;
    }

  SimpleGraphicsModel* getObjectModel() {
        return model;
    }

    void update(SimulationTime time) override;
};


#endif //PGR_PROJECT_SIMULATEDMODEL_H
