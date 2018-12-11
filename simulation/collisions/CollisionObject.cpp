//
// Created by Petr Flajsingr on 2018-12-03.
//

#include "CollisionObject.h"

bool PGRsim::Collision::RectArea::isIn(glm::vec3 point) {
  return pointA.x < point.x && pointA.y < point.y && pointA.z < point.z
      && pointB.x > point.x && pointB.y > point.y && pointB.z > point.z;
}

const glm::vec3 &PGRsim::Collision::CollisionObject::getNewPosition() const {
  return newPosition;
}

void PGRsim::Collision::CollisionObject::setNewPosition(const glm::vec3 &newPosition) {
  CollisionObject::newPosition = newPosition;
}

bool PGRsim::Collision::CollisionObject::isPositionChanged() const {
  return positionChanged;
}

void PGRsim::Collision::CollisionObject::setPositionChanged(bool positionChanged) {
  CollisionObject::positionChanged = positionChanged;
}
