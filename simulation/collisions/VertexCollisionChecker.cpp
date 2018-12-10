//
// Created by Petr Flajsingr on 2018-12-07.
//

#include <thread>
#include "VertexCollisionChecker.h"
#include <glm/gtx/intersect.hpp>
#include <GeoUtils.h>
#include <glm/gtx/normal.hpp>

PGRsim::Collision::VertexCollisionChecker::VertexCollisionChecker() {}

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

void PGRsim::Collision::VertexCollisionChecker::accurateCheck(std::vector<PGRsim::SimVertex *> &objects) {
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

  const float coef = 0.5f;

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

    auto lineLength = glm::length(glm::distance(vertex->getPreviousPosition(), vertex->getCurrectPosition()));
    if (std::abs(distance) > lineLength) {
      if (false && vertex->getParent() != v1->getParent()) {
        auto prev = vertex->getPreviousPosition();
        auto cur = vertex->getCurrectPosition();
        auto inter = PGRutils::baryToCartesian(position, v1Pos, v2Pos, v3Pos);
        StdoutLogger::getInstance().log("Collision aborted, prev: ", prev);
        StdoutLogger::getInstance().log("Collision aborted, curr: ", cur);
        StdoutLogger::getInstance().log("Collision aborted, inter: ", inter);
        StdoutLogger::getInstance().log("Collision aborted, distance: ", distance);
        StdoutLogger::getInstance().log("Collision aborted: move length: ", lineLength);
      }
      goto back_face_test;
    }
    auto pos = PGRutils::baryToCartesian(position, v1Pos, v2Pos, v3Pos);

    auto polyNormal = glm::triangleNormal(v1Pos, v2Pos, v3Pos);

    auto reaction = polyNormal * (lineLength - std::abs(distance)) * coef;
    vertex->setNewPosition(pos + reaction);
    vertex->setPositionChanged(true);

    reaction = reaction / 3.0f;

    v1->setNewPosition(v1->getCurrectPosition() - reaction);
    v1->setPositionChanged(true);
    v2->setNewPosition(v2->getCurrectPosition() - reaction);
    v2->setPositionChanged(true);
    v3->setNewPosition(v3->getCurrectPosition() - reaction);
    v3->setPositionChanged(true);

    StdoutLogger::getInstance().log("Collision detected, front face");
    StdoutLogger::getInstance().log("Collision detected, pos: ", pos);
    StdoutLogger::getInstance().log("Collision detected, distance: ", distance);
    StdoutLogger::getInstance().log("Collision detected: move length: ", lineLength);

    return true;
  }
  back_face_test:
  if (glm::intersectRayTriangle(
      vertex->getCurrectPosition(),
      lineDirReversed,
      v1->getCurrectPosition(),
      v2->getCurrectPosition(),
      v3->getCurrectPosition(),
      position,
      distance)) {

    auto lineLength = glm::length(glm::distance(vertex->getPreviousPosition(), vertex->getCurrectPosition()));
    if (std::abs(distance) > lineLength) {
      if (false && vertex->getParent() != v1->getParent()) {
        auto prev = vertex->getPreviousPosition();
        auto cur = vertex->getCurrectPosition();
        auto inter = PGRutils::baryToCartesian(position, v1Pos, v2Pos, v3Pos);
        StdoutLogger::getInstance().log("Collision aborted, prev: ", prev);
        StdoutLogger::getInstance().log("Collision aborted, curr: ", cur);
        StdoutLogger::getInstance().log("Collision aborted, inter: ", inter);
        StdoutLogger::getInstance().log("Collision aborted, distance: ", distance);
        StdoutLogger::getInstance().log("Collision aborted: move length: ", lineLength);
      }
      return false;
    }
    auto pos = PGRutils::baryToCartesian(position, v1Pos, v2Pos, v3Pos);

    auto polyNormal = glm::triangleNormal(v1Pos, v2Pos, v3Pos);

    auto reaction = polyNormal * (lineLength - (lineLength - std::abs(distance))) * coef;
    vertex->setNewPosition(pos - reaction);
    vertex->setPositionChanged(true);

    reaction = reaction / 3.0f;

    v1->setNewPosition(v1->getCurrectPosition() + reaction);
    v1->setPositionChanged(true);
    v2->setNewPosition(v2->getCurrectPosition() + reaction);
    v2->setPositionChanged(true);
    v3->setNewPosition(v3->getCurrectPosition() + reaction);
    v3->setPositionChanged(true);

    StdoutLogger::getInstance().log("Collision detected, back face");
    StdoutLogger::getInstance().log("Collision detected, pos: ", pos);
    StdoutLogger::getInstance().log("Collision detected, distance: ", distance);
    StdoutLogger::getInstance().log("Collision detected: move length: ", lineLength);

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
