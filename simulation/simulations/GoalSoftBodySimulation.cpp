//
// Created by Petr Flajsingr on 2018-12-02.
//

#include "GoalSoftBodySimulation.h"
PGRsim::GoalSoftBodySimulation::GoalSoftBodySimulation(SimpleGraphicsModel *model, SimpleGraphicsModel *goal)
    : model(model), goal(goal) {
  createVertices();

  createGoalVertices();

  connectSprings();
}

void PGRsim::GoalSoftBodySimulation::connectSprings() {

}

void PGRsim::GoalSoftBodySimulation::createVertices() {
  int vertexCount = 0;

  float vertexMass = 0 / 1;

  for (int i = 0; i < vertexCount; i++) {
    modelVertices.emplace_back(new SimVertex(vertexMass, Active, i, glm::vec3(0,0,0)));
    addObject(modelVertices[i]);
  }
}

void PGRsim::GoalSoftBodySimulation::createGoalVertices() {
  int vertexCount = 0;

  float vertexMass = 0 / 1;

  for (int i = 0; i < vertexCount; i++) {
    goalVertices.emplace_back(new SimVertex(vertexMass, Passive, i, glm::vec3(0,0,0)));
    addObject(goalVertices[i]);
  }
}
