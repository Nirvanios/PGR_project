//
// Created by Petr Flajsingr on 2018-12-01.
//

#ifndef PGR_PROJECT_SIMULATEDVERTEX_H
#define PGR_PROJECT_SIMULATEDVERTEX_H

#include "SimObject.h"

namespace PGRsim {

/**
 * Simulation of a single vertex which may be a part of a more complicated object.
 */
class SimVertex : public SimObject {
 private:
  int vertexId;

 protected:
 public:
  SimVertex(float mass, SimObjectType objectType, int vertexId, glm::vec3 position);

  void setVertexId(int id) {
    this->vertexId = id;
  }

  int getVertexId() {
    return vertexId;
  }
  void update(SimTime time) override;
};
}

#endif //PGR_PROJECT_SIMULATEDVERTEX_H
