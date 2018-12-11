//
// Created by Petr Flajsingr on 2018-12-03.
//

#ifndef PGR_PROJECT_COLLISIONOBJECT_H
#define PGR_PROJECT_COLLISIONOBJECT_H

#include <glm/glm.hpp>

namespace PGRsim::Collision {

/**
 * Axis aligned rectangular area.
 *
 * @author Petr Flajšingr
 */
struct RectArea {
  glm::vec3 pointA, pointB;

  /**
   * Check if a point is inside the rectangle.
   * @param point point to check
   * @return true if point is inside rectangle, false otherwise
   */
  bool isIn(glm::vec3 point);
};

/**
 * Interface for objects detected in collisions.
 *
 * @author Petr Flajšingr
 */
class CollisionObject {
 private:
  /**
   * Changed position after collision detection.
   */
  glm::vec3 newPosition;

  bool positionChanged = false;

 public:
  /**
   *
   * @return current position of an object
   */
  virtual glm::vec3 getPosition() = 0;

  /**
   *
   * @return position of an object after collision
   */
  const glm::vec3 &getNewPosition() const;

  void setNewPosition(const glm::vec3 &newPosition);

  bool isPositionChanged() const;

  void setPositionChanged(bool positionChanged);
};
}
#endif //PGR_PROJECT_COLLISIONOBJECT_H
