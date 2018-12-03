//
// Created by Petr on 28.11.2018.
//

#include "SimpleObject.h"
#include <iostream>
#include <glm/ext/matrix_transform.hpp>
#include <glm/vec4.hpp>

PGRsim::SimpleObject::SimpleObject(float mass, SimObjectType objectType, SimpleGraphicsModel* model) : SimObject(mass,
                                                                                                                objectType),
                                                                                                model(model) {
  currentPosition = model->getPosition();

  previousPosition = currentPosition;

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

void PGRsim::SimpleObject::update(SimTime time) {
    model->setPosition(currentPosition);
}

void PGRsim::SimpleObject::calcBoundingBox() {}
PGRsim::Collision::BoundingBox PGRsim::SimpleObject::getBoundingBox() {
  Collision::BoundingBox box;
  static auto model = glm::mat4(1.0f);
  auto translation = glm::translate(model, getCurrectPosition());
  box.pointA = translation * glm::vec4(boundingBox.pointA, 1.0);
  box.pointB = translation * glm::vec4(boundingBox.pointB, 1.0);
}
