//
// Created by Petr on 28.11.2018.
//

#include "SimModel.h"

PGRsim::SimModel::SimModel(float mass, SimObjectType objectType, SimpleGraphicsModel* model) : SimObject(mass,
                                                                                                                objectType),
                                                                                                model(model) {
  currentPosition = model->getPosition();

  previousPosition = currentPosition;
}

void PGRsim::SimModel::update(SimTime time) {
    model->setPosition(currentPosition);
}
