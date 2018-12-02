//
// Created by Petr on 28.11.2018.
//

#include "SimModel.h"

SimModel::SimModel(float mass, SimObjectType objectType, SimpleGraphicsModel* model) : SimObject(mass,
                                                                                                                objectType),
                                                                                                model(model) {
  currentPosition = model->getPosition();

  previousPosition = currentPosition;
}

void SimModel::update(SimTime time) {
    model->setPosition(currentPosition);
}
