//
// Created by Petr Flajsingr on 2018-12-07.
//

#include <StdoutLogger.h>
#include <SimVertex.h>
#include "VertexCollisionBins.h"

PGRsim::Collision::VertexCollisionBins::VertexCollisionBins(int xResolution,
                                                            int yResolution,
                                                            int zResolution,
                                                            const PGRsim::Collision::RectArea &area)
    : xResolution(xResolution), yResolution(yResolution), zResolution(zResolution), area(area) {
  binCount = xResolution * yResolution * zResolution;

  std::string msg = "Init bins\nBin count:"
      + std::to_string(binCount)
      + "\nResolution:\nx:"
      + std::to_string(xResolution)
      + " y:" + std::to_string(yResolution)
      + " z:" + std::to_string(zResolution);
  StdoutLogger::getInstance().logTime(msg);

  bins = new VertexCollisionBin[binCount];

  auto xStep = std::abs((area.pointA.x - area.pointB.x) / xResolution);
  auto yStep = std::abs((area.pointA.y - area.pointB.y) / yResolution);
  auto zStep = std::abs((area.pointA.z - area.pointB.z) / zResolution);

  for (int z = 0; z < zResolution; z++) {
    for (int y = 0; y < yResolution; y++) {
      auto yCoord = xResolution * y;
      for (int x = 0; x < xResolution; x++) {
        bins[x + yCoord + xResolution * yResolution * z].box = RectArea{
            .pointA = area.pointA + glm::vec3(x * xStep, y * yStep, z * zStep),
            .pointB = area.pointA + glm::vec3((x + 1) * xStep, (y + 1) * yStep, (z + 1) * zStep)
        };
      }
    }
  }
}

PGRsim::Collision::VertexCollisionBins::~VertexCollisionBins() {
  delete[] bins;
}

void PGRsim::Collision::VertexCollisionBins::addCollisionObject(PGRsim::SimVertex *object) {
  objects.emplace_back(object);
}

PGRsim::Collision::VertexCollisionBin *PGRsim::Collision::VertexCollisionBins::getBins() {
  return bins;
}

int PGRsim::Collision::VertexCollisionBins::getXResolution() const {
  return xResolution;
}

int PGRsim::Collision::VertexCollisionBins::getYResolution() const {
  return yResolution;
}

int PGRsim::Collision::VertexCollisionBins::getZResolution() const {
  return zResolution;
}

void PGRsim::Collision::VertexCollisionBins::recalculateBins(bool clearCalc) {
  for (int i = 0; i < binCount; i++) {
    bins[i].objects.clear();
  }

  for (auto object : objects) {
    object->setNewPosition(object->getCurrectPosition());
    for (int z = 0; z < zResolution; z++) {
      for (int y = 0; y < yResolution; y++) {
        auto yCoord = xResolution * y;
        for (int x = 0; x < xResolution; x++) {
          if (bins[x + yCoord + xResolution * yResolution * z].box.isIn(object->getPosition())) {
            bins[x + yCoord + xResolution * yResolution * z].objects.emplace_back(object);

            goto object_skip;
          }
        }
      }
    }
    object_skip:;
  }
}

int PGRsim::Collision::VertexCollisionBins::getBinCount() const {
  return binCount;
}

