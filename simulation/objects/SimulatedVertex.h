//
// Created by Petr Flajsingr on 2018-12-01.
//

#ifndef PGR_PROJECT_SIMULATEDVERTEX_H
#define PGR_PROJECT_SIMULATEDVERTEX_H

#include "SimulatedObject.h"

class SimulatedVertex : public SimulatedObject {
 private:
  int vertexId;

 protected:
 public:
  SimulatedVertex(float mass, SimulatedObjectType objectType, int vertexId, glm::vec3 position);

  void setVertexId(int id) {
   this->vertexId = id;
 }

 int getVertexId() {
   return vertexId;
 }
  void update(SimulationTime time) override;
};

#endif //PGR_PROJECT_SIMULATEDVERTEX_H
