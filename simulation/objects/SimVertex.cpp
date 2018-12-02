//
// Created by Petr Flajsingr on 2018-12-01.
//

#include "SimVertex.h"

SimVertex::SimVertex(float mass, SimObjectType objectType, int vertexId, glm::vec3 position) : SimObject(mass,
                                                                                                             objectType),
                                                                                             vertexId(vertexId) {
  currentPosition = position;
  previousPosition = position;
}

void SimVertex::update(SimTime time) {
  // TODO: nastavit pozici pro výstupní vertex

}

