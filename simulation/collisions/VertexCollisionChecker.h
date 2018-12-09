//
// Created by Petr Flajsingr on 2018-12-07.
//

#ifndef PGR_PROJECT_COLLISIONCHECKER_H
#define PGR_PROJECT_COLLISIONCHECKER_H

#include "VertexCollisionBins.h"
#include <ComplexObject.h>

namespace PGRsim::Collision {

class VertexCollisionChecker {
 private:
  VertexCollisionBins bins = VertexCollisionBins(10, 10, 10, Collision::RectArea{
      .pointA = glm::vec3(-3, -3, -3),
      .pointB = glm::vec3(3, 3, 3)
  });

  void accurateCheck(std::vector<SimVertex *> &objects);

 public:
  VertexCollisionChecker();

  void addObjects(const std::vector<SimVertex *> &objects);

  void addObject(SimVertex *object);

  void checkCollisions();

  static bool checkIntersection(SimVertex *vertex, SimVertex *v1, SimVertex *v2, SimVertex *v3);

  void applyChanges();
};
}

#endif //PGR_PROJECT_COLLISIONCHECKER_H
