//
// Created by Petr Flajsingr on 2018-12-07.
//

#ifndef PGR_PROJECT_COLLISIONCHECKER_H
#define PGR_PROJECT_COLLISIONCHECKER_H

#include "VertexCollisionBins.h"
#include <ComplexObject.h>

namespace PGRsim::Collision {

/**
 * Collision checker using space division via axis aligned bins.
 * Checker uses ray tracing to check if any of vertices has passed
 * through a triangle in a simulation step.
 *
 * @author Petr Flajšingr
 */
class VertexCollisionChecker {
 private:
  VertexCollisionBins bins =
      VertexCollisionBins(10, 10, 3, Collision::RectArea{
          .pointA = glm::vec3(-3, -3, -3),
          .pointB = glm::vec3(3, 3, 3)
      });

  /**
   * Check collisions for each pair of objects
   * in a vector (used with objects within a bin)
   * @param objects objects to check collisions for
   */
  void accurateCheck(const std::vector<SimVertex *> &objects);

 public:
  VertexCollisionChecker();

  /**
   * Add vector of objects for collision checking.
   * @param objects objects to use in collision checking
   */
  void addObjects(const std::vector<SimVertex *> &objects);

  /**
   * Add object for collision checking.
   * @param object object used in collision checking.
   */
  void addObject(SimVertex *object);

  /**
   * Check for collisions. Should be called only once in a time step.
   * Prepares new positions of objects but doesn't apply them.
   */
  void checkCollisions();

  /**
   * Check intersection of a vertex with a triangle.
   * Sets new position of a vertex if a collision has occured.
   *
   * @param vertex vertex to check collision for
   * @param v1 first vertex of a triangle
   * @param v2 second vertex of a triangle
   * @param v3 third vertex of a triangle
   * @return true if collision occured, false otherwise
   */
  static bool checkIntersection(SimVertex *vertex, SimVertex *v1, SimVertex *v2, SimVertex *v3);

  /**
   * Apply new positions to simulation object.
   */
  void applyChanges();
};
}

#endif //PGR_PROJECT_COLLISIONCHECKER_H
