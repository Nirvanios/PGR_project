//
// Created by Petr Flajsingr on 2018-12-01.
//

#include "SimVertex.h"

PGRsim::SimVertex::SimVertex(float mass, PGRsim::SimObjectType objectType, int vertexId, glm::vec3 position)
    : SimObject(mass,
                                                                                                             objectType),
                                                                                             vertexId(vertexId) {
  currentPosition = position;
  previousPosition = position;
}

void PGRsim::SimVertex::update(SimTime time) {
}

