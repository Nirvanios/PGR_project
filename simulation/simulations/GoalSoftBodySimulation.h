//
// Created by Petr Flajsingr on 2018-12-02.
//

#ifndef PGR_PROJECT_GOALSOFTBODYSIMULATION_H
#define PGR_PROJECT_GOALSOFTBODYSIMULATION_H

#include "DEPRECATED_SimpleGraphicsModel.h"
#include <Vertex.h>
#include "Simulation.h"

namespace PGRsim {
class GoalSoftBodySimulation : public Simulation {
 private:
  DEPRECATED_SimpleGraphicsModel *model;
  DEPRECATED_SimpleGraphicsModel *goal;

  std::vector<Vertex *> modelVertices;
  std::vector<Vertex *> goalVertices;

  void createVertices();

  void createGoalVertices();

  void connectSprings();

 protected:
 public:
  GoalSoftBodySimulation(DEPRECATED_SimpleGraphicsModel *model, DEPRECATED_SimpleGraphicsModel *goal);

};
}
#endif //PGR_PROJECT_GOALSOFTBODYSIMULATION_H
