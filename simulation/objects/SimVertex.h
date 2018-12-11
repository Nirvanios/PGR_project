//
// Created by Petr Flajsingr on 2018-12-01.
//

#ifndef PGR_PROJECT_SIMULATEDVERTEX_H
#define PGR_PROJECT_SIMULATEDVERTEX_H

#include "SimpleObject.h"
#include <vector>
#include <array>


namespace PGRsim {
class ComplexObject;

/**
 * Simulation of a single vertex which may be a part of a more complicated object.
 *
 * @author Petr Flajšingr
 */
class SimVertex : public SimObject, public Collision::CollisionObject {
 private:
  int vertexId;

  /**
   * Indices in which the vertex is used.
   */
  std::vector<std::array<int, 3>> indices;

  ComplexObject *parent;

 public:
  SimVertex(float mass, SimObjectType objectType, int vertexId, glm::vec3 position, ComplexObject *parent);

  void setVertexId(int id) {
    this->vertexId = id;
  }

  int getVertexId() {
    return vertexId;
  }
  void update(SimTime time) override;

  glm::vec3 getPosition() override;

  void addIndex(int indexA, int indexB, int indexC);

  const std::vector<std::array<int, 3>> &getIndices() const;

  ComplexObject *getParent() const;
  void setParent(ComplexObject *parent);
};
}

#endif //PGR_PROJECT_SIMULATEDVERTEX_H
