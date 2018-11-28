//
// Created by Petr on 28.11.2018.
//

#ifndef PGR_PROJECT_SIMULATEDMODEL_H
#define PGR_PROJECT_SIMULATEDMODEL_H


#include "SimulatedObject.h"

class SimulatedModel: public SimulatedObject {
private:
    ObjectModel model;
public:
    SimulatedModel(float mass, SimulatedObjectType objectType, ObjectModel model);

    void setObjectModel(ObjectModel model) {
        this->model = model;
    }

    ObjectModel getObjectModel() {
        return model;
    }

    void Update(SimulationTime time) override;
};


#endif //PGR_PROJECT_SIMULATEDMODEL_H
