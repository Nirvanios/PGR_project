//
// Created by Petr Flajsingr on 2018-12-07.
//

#include <StdoutLogger.h>
#include "CollisionBins.h"

PGRsim::Collision::CollisionBins::CollisionBins(int xResolution,
                                                int yResolution,
                                                int zResolution,
                                                const PGRsim::Collision::BoundingBox &area)
    : xResolution(xResolution), yResolution(yResolution), zResolution(zResolution), area(area) {
  binCount = xResolution * yResolution * zResolution;

  std::string msg = "Init bins\nBin count:"
      + std::to_string(binCount)
      + "\nResolution:\nx:"
      + std::to_string(xResolution)
      + " y:" + std::to_string(yResolution)
      + " z:" + std::to_string(zResolution);
  StdoutLogger::getInstance().logTime(msg);

  bins = new CollisionBin[binCount];

  auto xStep = std::abs(static_cast<int>((area.pointA.x - area.pointB.x) / xResolution));
  auto yStep = std::abs(static_cast<int>((area.pointA.y - area.pointB.y) / yResolution));
  auto zStep = std::abs(static_cast<int>((area.pointA.z - area.pointB.z) / zResolution));

  for (int z = 0; z < zResolution; z++) {
    for (int y = 0; y < yResolution; y++) {
      auto yCoord = xResolution * y;
      for (int x = 0; x < xResolution; x++) {
        bins[x + yCoord + xResolution * yResolution * z].box = BoundingBox{
            .pointA = area.pointA + glm::vec3(x * xStep, y * yStep, z * zStep),
            .pointB = area.pointA + glm::vec3((x + 1) * xStep, (y + 1) * yStep, (z + 1) * zStep)
        };
      }
    }
  }

  recalculateBins(true);
}

PGRsim::Collision::CollisionBins::~CollisionBins() {
  delete[] bins;
}

void PGRsim::Collision::CollisionBins::addCollisionObject(PGRsim::Collision::CollisionObject *object) {
  objects.emplace_back(object);
}

PGRsim::Collision::CollisionBin *PGRsim::Collision::CollisionBins::getBins() {
  return bins;
}

int PGRsim::Collision::CollisionBins::getXResolution() const {
  return xResolution;
}

int PGRsim::Collision::CollisionBins::getYResolution() const {
  return yResolution;
}

int PGRsim::Collision::CollisionBins::getZResolution() const {
  return zResolution;
}

void PGRsim::Collision::CollisionBins::recalculateBins(bool clearCalc) {
  if (true) {
    for (int i = 0; i < binCount; i++) {
      bins[i].objects.clear();
    }

    for (auto object : objects) {
      for (int z = 0; z < zResolution - 1; z++) {
        for (int y = 0; y < yResolution - 1; y++) {
          auto yCoord = xResolution * y;
          for (int x = 0; x < xResolution - 1; x++) {
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
}

int PGRsim::Collision::CollisionBins::getBinCount() const {
  return binCount;
}

