//
// Created by Petr on 28.11.2018.
//

#include "SimulatedModel.h"

SimulatedModel::SimulatedModel(float mass, SimulatedObjectType objectType, ObjectModel model) : SimulatedObject(mass,
                                                                                                                objectType),
                                                                                                model(model) {
    // TODO: nastaveni currentPosition na pozici modelu
    previousPosition = currentPosition;
}

void SimulatedModel::update(SimulationTime time) {
    // TODO: posun model do current position
}
