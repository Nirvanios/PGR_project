//
// Created by Petr Flajsingr on 2018-12-01.
//

#ifndef PGR_PROJECT_SOFTBODYSIMULATION_H
#define PGR_PROJECT_SOFTBODYSIMULATION_H

#include "Simulation.h"
#include "objects/SimulatedVertex.h"
class SoftBodySimulation : public Simulation {
 private:
 protected:
  std::vector<SimulatedVertex*> vertices;
 public:
  SoftBodySimulation();

};

#endif //PGR_PROJECT_SOFTBODYSIMULATION_H
