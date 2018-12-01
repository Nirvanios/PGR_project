//
// Created by Petr on 28.11.2018.
//

#include "SimulatedModel.h"

SimulatedModel::SimulatedModel(float mass, SimulatedObjectType objectType, SimpleGraphicsModel* model) : SimulatedObject(mass,
                                                                                                                objectType),
                                                                                                model(model) {
  currentPosition = model->getPosition();

  previousPosition = currentPosition;
}

void SimulatedModel::update(SimulationTime time) {
    model->setPosition(currentPosition);
}
