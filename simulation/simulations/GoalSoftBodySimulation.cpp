//
// Created by Petr Flajsingr on 2018-12-02.
//

#include "GoalSoftBodySimulation.h"
GoalSoftBodySimulation::GoalSoftBodySimulation(SimpleGraphicsModel *model, SimpleGraphicsModel *goal)
    : model(model), goal(goal) {
  createVertices();

  createGoalVertices();

  connectSprings();
}

void GoalSoftBodySimulation::connectSprings() {

}

void GoalSoftBodySimulation::createVertices() {
  int vertexCount = 0;

  float vertexMass = 0 / 1;

  for (int i = 0; i < vertexCount; i++) {
    modelVertices.emplace_back(new SimVertex(vertexMass, Active, i, model->getVertices()[i]));
    addObject(modelVertices[i]);
  }
}

void GoalSoftBodySimulation::createGoalVertices() {
  int vertexCount = 0;

  float vertexMass = 0 / 1;

  for (int i = 0; i < vertexCount; i++) {
    goalVertices.emplace_back(new SimVertex(vertexMass, Passive, i, goal->getVertices()[i]));
    addObject(goalVertices[i]);
  }
}
