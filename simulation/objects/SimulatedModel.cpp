//
// Created by Petr on 28.11.2018.
//

#include "SimulatedModel.h"

float temp = 10;

// TODO: remove temp
SimulatedModel::SimulatedModel(float mass, SimulatedObjectType objectType, ObjectModel model) : SimulatedObject(mass,
                                                                                                                objectType),
                                                                                                model(model) {
  currentPosition = glm::vec3(temp, 0, temp);


  if (mass == 1.2f) {
    currentPosition = glm::vec3(temp - 5, 0, temp - 4);
  }
  temp += 5;
  previousPosition = currentPosition;
}

void SimulatedModel::update(SimulationTime time) {
    // TODO: posun model do current position
}
