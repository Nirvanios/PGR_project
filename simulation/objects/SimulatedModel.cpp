//
// Created by Petr on 28.11.2018.
//

#include "SimulatedModel.h"

float temp = 10;

SimulatedModel::SimulatedModel(float mass, SimulatedObjectType objectType, ObjectModel model) : SimulatedObject(mass,
                                                                                                                objectType),
                                                                                                model(model) {
  currentPosition = glm::vec3(temp, 0, temp);
  temp += 5;
  previousPosition = currentPosition;
}

void SimulatedModel::update(SimulationTime time) {
    // TODO: posun model do current position
}
