//
// Created by Petr on 28.11.2018.
//

#include "SimpleObject.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec4.hpp>

PGRsim::SimpleObject::SimpleObject(float mass,
                                   PGRsim::SimObjectType objectType,
                                   PGRgraphics::SimpleGraphicsModel *model) : SimObject(mass,
                                                                                        objectType),
                                                                              model(model) {
  currentPosition = model->getPosition();

  previousPosition = currentPosition;

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

void PGRsim::SimpleObject::update(PGRsim::SimTime time) {
    model->setPosition(currentPosition);
}

void PGRsim::SimpleObject::calcBoundingBox() {}
PGRsim::Collision::BoundingBox PGRsim::SimpleObject::getBoundingBox() {
  Collision::BoundingBox box{};
  static auto model = glm::mat4(1.0f);
  auto translation = glm::translate(model, getCurrectPosition());
  box.pointA = translation * glm::vec4(boundingBox.pointA, 1.0);
  box.pointB = translation * glm::vec4(boundingBox.pointB, 1.0);
}
