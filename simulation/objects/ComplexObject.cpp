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
    simVertices.emplace_back(new SimVertex(vertexMass, type, i, model->getVertices()[i]));
  }
}

void PGRsim::ComplexObject::update(PGRsim::SimTime time) {
  for (int i = 0; i < model->getVertices().size(); i++) {
    model->setVertex(i, simVertices[i]->getCurrectPosition());
  }
  model->computeNormals();
}

void PGRsim::ComplexObject::calcBoundingBox() {
  boundingBox.pointA = model->getVertices()[0];
  glm::vec3 max = boundingBox.pointA;
  for (int i = 0; i < model->getVertices().size(); i ++) {
    if (boundingBox.pointA.x > model->getVertices()[i].x) {
      boundingBox.pointA.x = model->getVertices()[i].x;
    } else if (boundingBox.pointB.x < model->getVertices()[i].x) {
      boundingBox.pointB.x = model->getVertices()[i].x;
    }

    if (boundingBox.pointA.y > model->getVertices()[i + 1].y) {
      boundingBox.pointA.y = model->getVertices()[i + 1].y;
    } else if (boundingBox.pointB.y < model->getVertices()[i + 1].y) {
      boundingBox.pointB.y = model->getVertices()[i + 1].y;
    }

    if (boundingBox.pointA.z > model->getVertices()[i + 2].z) {
      boundingBox.pointA.z = model->getVertices()[i + 2].z;
    } else if (boundingBox.pointB.z < model->getVertices()[i + 2].z) {
      boundingBox.pointB.z = model->getVertices()[i + 2].z;
    }
  }
}

void PGRsim::ComplexObject::addSpring(float stiffness, float damping, int vertexID1, int vertexID2) {
  springs.emplace_back(new SnappableSpring(stiffness, damping, simVertices[vertexID1], simVertices[vertexID2], .8f));
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


