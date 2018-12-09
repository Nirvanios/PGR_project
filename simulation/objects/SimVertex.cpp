//
// Created by Petr Flajsingr on 2018-12-01.
//
#include "SimVertex.h"

PGRsim::SimVertex::SimVertex(
    float mass,
    PGRsim::SimObjectType objectType,
    int vertexId, glm::vec3 position,
    ComplexObject *parent)
    : SimObject(mass,
                objectType),
      vertexId(vertexId), parent(parent) {
  currentPosition = position;
  previousPosition = position;
}

void PGRsim::SimVertex::update(SimTime time) {
}

void PGRsim::SimVertex::calcBoundingBox() {

}

glm::vec3 PGRsim::SimVertex::getPosition() {
  return currentPosition;
}

void PGRsim::SimVertex::addIndex(int indexA, int indexB, int indexC) {
  std::array<int, 3> indices = {indexA, indexB, indexC};
  this->indices.emplace_back(indices);
}

const std::vector<std::array<int, 3>> &PGRsim::SimVertex::getIndices() const {
  return indices;
}

PGRsim::ComplexObject *PGRsim::SimVertex::getParent() const {
  return parent;
}

void PGRsim::SimVertex::setParent(PGRsim::ComplexObject *parent) {
  SimVertex::parent = parent;
}

