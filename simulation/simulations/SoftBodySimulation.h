//
// Created by Petr Flajsingr on 2018-12-01.
//

#ifndef PGR_PROJECT_SOFTBODYSIMULATION_H
#define PGR_PROJECT_SOFTBODYSIMULATION_H

#include "Simulation.h"
#include "Vertex.h"

namespace PGRsim {
class SoftBodySimulation : public Simulation {
 private:
 protected:
  std::vector<Vertex *> vertices;
 public:
  SoftBodySimulation();

  std::vector<Vertex *> getVertices() {
    return vertices;
  }
};
}
#endif //PGR_PROJECT_SOFTBODYSIMULATION_H
