//
// Created by Petr Flajsingr on 2018-12-02.
//

#ifndef PGR_PROJECT_GOALSOFTBODYSIMULATION_H
#define PGR_PROJECT_GOALSOFTBODYSIMULATION_H

#include "ComplexGraphicsModel.h"
#include <Vertex.h>
#include "Simulation.h"

namespace PGRsim {
class GoalSoftBodySimulation : public Simulation {
 private:
  PGRgraphics::ComplexGraphicsModel *model;
  PGRgraphics::SimpleGraphicsModel *goal;

  std::vector<Vertex *> modelVertices;
  std::vector<Vertex *> goalVertices;

  void createVertices();

  void createGoalVertices();

  void connectSprings();

 protected:
 public:
  GoalSoftBodySimulation(PGRgraphics::ComplexGraphicsModel *model, PGRgraphics::SimpleGraphicsModel *goal);

};
}
#endif //PGR_PROJECT_GOALSOFTBODYSIMULATION_H
