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
  // triangle vertices
  auto v1Pos = v1->getCurrectPosition();
  auto v2Pos = v2->getCurrectPosition();
  auto v3Pos = v3->getCurrectPosition();

  // "bounce" coefficient
  const float coef = 1.0f;

  auto movementDirection = glm::normalize(vertex->getCurrectPosition() - vertex->getPreviousPosition());

  float distance;
  glm::vec2 baryPosition;

  if (glm::intersectRayTriangle(
      vertex->getPreviousPosition(),
      movementDirection,
      v1->getCurrectPosition(),
      v2->getCurrectPosition(),
      v3->getCurrectPosition(),
      baryPosition,
      distance)) {

    auto moveLength = glm::distance(vertex->getPreviousPosition(), vertex->getCurrectPosition());

    // if ray intersects the triangle further away than the movement distance - abort
    if (std::abs(distance) > moveLength) {
      return false;
    }

    auto intersection = PGRutils::baryToCartesian(baryPosition, v1Pos, v2Pos, v3Pos);

    auto triangleNormal = glm::triangleNormal(v1Pos, v2Pos, v3Pos);

    auto reaction = triangleNormal * ((moveLength - std::abs(distance)) + (std::abs(distance) * coef));

    // check from which side the triangle has been hit
    auto planeVec = vertex->getPreviousPosition() - intersection;
    auto angle = glm::dot(planeVec, triangleNormal);
    if (angle < 0) {
      reaction = -reaction;
    }

    // accumulate position change
    vertex->setNewPosition(vertex->getNewPosition() + reaction);
    vertex->setPositionChanged(true);

    reaction /= 3.0f;

    // apply position change to the triangle
    v1->setNewPosition(v1->getNewPosition() - reaction * (1 - baryPosition.x - baryPosition.y));
    v1->setPositionChanged(true);
    v2->setNewPosition(v2->getNewPosition() - reaction * baryPosition.x);
    v2->setPositionChanged(true);
    v3->setNewPosition(v3->getNewPosition() - reaction * baryPosition.y);
    v3->setPositionChanged(true);
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