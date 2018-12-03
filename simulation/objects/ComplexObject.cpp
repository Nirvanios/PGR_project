//
// Created by Petr Flajsingr on 2018-12-03.
//

#include "ComplexObject.h"

PGRsim::ComplexObject::ComplexObject(float mass, SoftBodyGraphicsModel *model)
    : SimObject(mass, Active), model(model) {}

void PGRsim::ComplexObject::update(PGRsim::SimTime time) {
  // TODO: nastavit vertexy při kroku simulace
}

void PGRsim::ComplexObject::calcBoundingBox() {
  boundingBox.pointA = glm::vec3(model->getVertices()[0], model->getVertices()[1], model->getVertices()[2]);
  glm::vec3 max = boundingBox.pointA;
  for (int i = 0; i < model->getVerticesSize(); i += 3) {
    if (boundingBox.pointA.x > model->getVertices()[i]) {
      boundingBox.pointA.x = model->getVertices()[i];
    } else if (boundingBox.pointB.x < model->getVertices()[i]) {
      boundingBox.pointB.x = model->getVertices()[i];
    }
    if (boundingBox.pointA.y > model->getVertices()[i + 1]) {
      boundingBox.pointA.y = model->getVertices()[i + 1];
    } else if (boundingBox.pointB.y < model->getVertices()[i + 1]) {
      boundingBox.pointB.y = model->getVertices()[i + 1];
    }
    if (boundingBox.pointA.z > model->getVertices()[i + 2]) {
      boundingBox.pointA.z = model->getVertices()[i + 2];
    } else if (boundingBox.pointB.z < model->getVertices()[i + 2]) {
      boundingBox.pointB.z = model->getVertices()[i + 2];
    }
  }
}
