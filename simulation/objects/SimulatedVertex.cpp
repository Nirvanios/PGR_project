//
// Created by Petr Flajsingr on 2018-12-01.
//

#include "SimulatedVertex.h"

SimulatedVertex::SimulatedVertex(float mass, SimulatedObjectType objectType, int vertexId, glm::vec3 position) : SimulatedObject(mass,
                                                                                                             objectType),
                                                                                             vertexId(vertexId) {
  currentPosition = position;
  previousPosition = position;
}

void SimulatedVertex::update(SimulationTime time) {
  // TODO: nastavit pozici pro výstupní vertex

}

