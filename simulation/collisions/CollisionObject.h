//
// Created by Petr Flajsingr on 2018-12-03.
//

#ifndef PGR_PROJECT_COLLISIONOBJECT_H
#define PGR_PROJECT_COLLISIONOBJECT_H

#include <glm/glm.hpp>

namespace PGRsim::Collision {

/**
 * Axis aligned bounding box
 */
struct RectArea {
  glm::vec3 pointA, pointB;

  bool isIn(glm::vec3 point) {
    return pointA.x < point.x && pointA.y < point.y && pointA.z < point.z
        && pointB.x > point.x && pointB.y > point.y && pointB.z > point.z;
  }
};

/**
 * Interface for objects detected in collisions.
 */
class CollisionObject {
 protected:
  RectArea boundingBox;

  glm::vec3 newPosition;

  bool positionChanged = false;
 public:
  virtual void calcBoundingBox() = 0;

  virtual RectArea getBoundingBox() {
    return boundingBox;
  }

  virtual glm::vec3 getPosition() = 0;

  const glm::vec3 &getNewPosition() const {
    return newPosition;
  }

  void setNewPosition(const glm::vec3 &newPosition) {
    CollisionObject::newPosition = newPosition;
  }

  bool isPositionChanged() const {
    return positionChanged;
  }

  void setPositionChanged(bool positionChanged) {
    CollisionObject::positionChanged = positionChanged;
  }
};
}
#endif //PGR_PROJECT_COLLISIONOBJECT_H
