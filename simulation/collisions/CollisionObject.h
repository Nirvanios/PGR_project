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
struct BoundingBox {
  glm::vec3 pointA, pointB;
};

/**
 * Interface for objects detected in collisions.
 */
class CollisionObject {
 protected:
  BoundingBox boundingBox;
 public:
  virtual void calcBoundingBox() = 0;

  virtual BoundingBox getBoundingBox() {
    return boundingBox;
  }
};
}
#endif //PGR_PROJECT_COLLISIONOBJECT_H
