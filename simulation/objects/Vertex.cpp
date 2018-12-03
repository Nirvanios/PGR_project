//
// Created by Petr Flajsingr on 2018-12-01.
//

#include "Vertex.h"

PGRsim::Vertex::Vertex(float mass, PGRsim::SimObjectType objectType, int vertexId, glm::vec3 position) : SimObject(mass,
                                                                                                             objectType),
                                                                                             vertexId(vertexId) {
  currentPosition = position;
  previousPosition = position;
}

void PGRsim::Vertex::update(SimTime time) {
  // TODO: nastavit pozici pro výstupní vertex

}

