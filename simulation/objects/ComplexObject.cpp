//
// Created by Petr Flajsingr on 2018-12-03.
//

#include "ComplexObject.h"

PGRsim::ComplexObject::ComplexObject(float mass, ComplexGraphicsModel *model)
    : SimObject(mass, Active), model(model) {}

void PGRsim::ComplexObject::update(PGRsim::SimTime time) {
  // TODO: nastavit vertexy při kroku simulace
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
