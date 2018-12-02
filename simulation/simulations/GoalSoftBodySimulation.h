//
// Created by Petr Flajsingr on 2018-12-02.
//

#ifndef PGR_PROJECT_GOALSOFTBODYSIMULATION_H
#define PGR_PROJECT_GOALSOFTBODYSIMULATION_H

#include <SimpleGraphicsModel.h>
#include <SimVertex.h>
#include "Simulation.h"

class GoalSoftBodySimulation : public Simulation {
 private:
  SimpleGraphicsModel* model;
  SimpleGraphicsModel* goal;

  std::vector<SimVertex*> modelVertices;
  std::vector<SimVertex*> goalVertices;

  void createVertices();

  void createGoalVertices();

  void connectSprings();

 protected:
 public:
  GoalSoftBodySimulation(SimpleGraphicsModel *model, SimpleGraphicsModel *goal);

};

#endif //PGR_PROJECT_GOALSOFTBODYSIMULATION_H
