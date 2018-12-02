//
// Created by Petr Flajsingr on 2018-12-01.
//

#ifndef PGR_PROJECT_SOFTBODYSIMULATION_H
#define PGR_PROJECT_SOFTBODYSIMULATION_H

#include "Simulation.h"
#include "SimVertex.h"
class SoftBodySimulation : public Simulation {
 private:
 protected:
  std::vector<SimVertex*> vertices;
 public:
  SoftBodySimulation();

  std::vector<SimVertex*> getVertices() {
    return vertices;
  }
};

#endif //PGR_PROJECT_SOFTBODYSIMULATION_H
