//
// Created by Petr Flajsingr on 2018-12-03.
//

#include <springs/SnappableSpring.h>
#include "ComplexObject.h"

PGRsim::ComplexObject::ComplexObject(float mass, PGRsim::SimObjectType type, PGRgraphics::ComplexGraphicsModel *model)
    : SimObjectWithModel(mass, type), model(model) {
  simVertices.reserve(model->getVertices().size());
  float vertexMass = mass / model->getVertices().size();
  for (int i = 0; i < model->getVertices().size(); i++) {
    auto simVertex = new SimVertex(vertexMass, type, i, model->getVertices()[i], this);

    for (int j = 0; j < model->getVertexIndices().size(); j += 3) {
      if (model->getVertexIndices()[j] == i
          || model->getVertexIndices()[j + 1] == i
          || model->getVertexIndices()[j + 2] == i) {
        simVertex->addIndex(model->getVertexIndices()[j],
                            model->getVertexIndices()[j + 1],
                            model->getVertexIndices()[j + 2]);
      }
    }

    simVertices.emplace_back(simVertex);
  }
}

void PGRsim::ComplexObject::update(PGRsim::SimTime time) {
  for (int i = 0; i < model->getVertices().size(); i++) {
    model->setVertex(i, simVertices[i]->getCurrectPosition());
  }
  model->computeNormals();
}

void PGRsim::ComplexObject::addSpring(float stiffness, float damping, int vertexID1, int vertexID2) {
  springs.emplace_back(new Spring(stiffness, damping, simVertices[vertexID1], simVertices[vertexID2]));
}

void PGRsim::ComplexObject::addConstraint(const glm::vec3 &position, int vertexID) {
  constraints.emplace_back(new PointConstraint(position, simVertices[vertexID]));
}

void PGRsim::ComplexObject::addConstraint(float length, int vertexID1, int vertexID2) {
  constraints.emplace_back(new LengthConstraint(simVertices[vertexID1], simVertices[vertexID2], length));
}

void PGRsim::ComplexObject::removeIndices(int vertexID) {
  std::vector<int> newIndices;
  auto oldIndices = model->getVertexIndices();
  newIndices.reserve(oldIndices.size());

  for (int i = 0; i < oldIndices.size(); i += 3) {
    if (oldIndices[i] == vertexID ||
        oldIndices[i + 1] == vertexID ||
        oldIndices[i + 2] == vertexID) {
      continue;
    }

    newIndices.emplace_back(oldIndices[i]);
    newIndices.emplace_back(oldIndices[i + 1]);
    newIndices.emplace_back(oldIndices[i + 2]);
  }
  model->setVertexIndices(newIndices);
}

PGRsim::ComplexObject *PGRsim::ComplexObject::clone(PGRsim::SimObjectType type) {
  auto result = new ComplexObject(getMass(), type, model->clone());
  return result;
}
void PGRsim::ComplexObject::addSnappableSpring(float stiffness,
                                               float damping,
                                               int vertexID1,
                                               int vertexID2,
                                               float limit) {
  springs.emplace_back(new SnappableSpring(stiffness, damping, simVertices[vertexID1], simVertices[vertexID2], limit));
}

void PGRsim::ComplexObject::addVertex(PGRsim::SimVertex *vertex) {
  simVertices.emplace_back(vertex);
}

