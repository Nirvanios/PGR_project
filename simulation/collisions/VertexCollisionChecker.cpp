//
// Created by Petr Flajsingr on 2018-12-07.
//

#include <thread>
#include "VertexCollisionChecker.h"
#include <glm/gtx/intersect.hpp>
#include <GeoUtils.h>
#include <glm/gtx/normal.hpp>
#include <iostream>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wwritable-strings"
PGRsim::Collision::VertexCollisionChecker::VertexCollisionChecker() = default;

void PGRsim::Collision::VertexCollisionChecker::addObjects(const std::vector<PGRsim::SimVertex *> &objects) {
  for (auto object : objects) {
    bins.addCollisionObject(object);
  }
}

void PGRsim::Collision::VertexCollisionChecker::addObject(PGRsim::SimVertex *object) {
  bins.addCollisionObject(object);
}

void PGRsim::Collision::VertexCollisionChecker::checkCollisions() {
  bins.recalculateBins();

  for (int i = 0; i < bins.getBinCount(); i++) {
    if (!bins.getBins()[i].objects.empty()) {
      accurateCheck(bins.getBins()[i].objects);
    }
  }
}

void PGRsim::Collision::VertexCollisionChecker::accurateCheck(const std::vector<PGRsim::SimVertex *> &objects) {
  glm::vec3 previousPosition, currentPosition;
  for (auto collidingVertex : objects) {
    for (auto toCheckVertex : objects) {
      if (toCheckVertex == collidingVertex) {
        continue;
      }
      for (auto index : toCheckVertex->getIndices()) {
        if (collidingVertex->getVertexId() != index[0]
            && collidingVertex->getVertexId() != index[1]
            && collidingVertex->getVertexId() != index[2]) {
          auto v1 = toCheckVertex->getParent()->getSimVertices()[index[0]];
          auto v2 = toCheckVertex->getParent()->getSimVertices()[index[1]];
          auto v3 = toCheckVertex->getParent()->getSimVertices()[index[2]];
          if (checkIntersection(collidingVertex, v1, v2, v3)) {
            goto next;
          }
        }
      }
    }
    next:
    {}
  }
}

bool PGRsim::Collision::VertexCollisionChecker::checkIntersection(SimVertex *vertex,
                                                                  SimVertex *v1,
                                                                  SimVertex *v2,
                                                                  SimVertex *v3) {
  auto v1Pos = v1->getCurrectPosition();
  auto v2Pos = v2->getCurrectPosition();
  auto v3Pos = v3->getCurrectPosition();

  const float coef = 1.0f;

  auto lineDir = glm::normalize(vertex->getCurrectPosition() - vertex->getPreviousPosition());
  auto lineDirReversed = glm::normalize(vertex->getPreviousPosition() - vertex->getCurrectPosition());

  float distance;
  glm::vec2 position;

  if (glm::intersectRayTriangle(
      vertex->getPreviousPosition(),
      lineDir,
      v1->getCurrectPosition(),
      v2->getCurrectPosition(),
      v3->getCurrectPosition(),
      position,
      distance)) {

    auto lineLength = glm::distance(vertex->getPreviousPosition(), vertex->getCurrectPosition());
    if (std::abs(distance) > lineLength) {
      return false;
    }
    auto pos = PGRutils::baryToCartesian(position, v1Pos, v2Pos, v3Pos);

    auto polyNormal = glm::triangleNormal(v1Pos, v2Pos, v3Pos);

    glm::vec3 reaction;
    reaction = polyNormal * lineLength * coef;

    auto planeVec = vertex->getPreviousPosition() - pos;
    auto dot = glm::dot(planeVec, polyNormal);

    if (dot > 0) {
      vertex->setNewPosition(vertex->getNewPosition() + reaction);
    } else {
      vertex->setNewPosition(vertex->getNewPosition() - reaction);
    }

    vertex->setPositionChanged(true);

    reaction = reaction / 3.0f;

    /*v1->setNewPosition(v1->getNewPosition() - reaction);
    v1->setPositionChanged(true);
    v2->setNewPosition(v2->getNewPosition() - reaction);
    v2->setPositionChanged(true);
    v3->setNewPosition(v3->getNewPosition() - reaction);
    v3->setPositionChanged(true);*/
    return true;
  }
  return false;
}

void PGRsim::Collision::VertexCollisionChecker::applyChanges() {
  for (int i = 0; i < bins.getBinCount(); i++) {
    for (auto object : bins.getBins()[i].objects) {
      if (object->isPositionChanged()) {
        object->setCurrentPosition(object->getNewPosition());
        object->setPositionChanged(false);
      }
    }
  }
}

#pragma clang diagnostic pop