//
// Created by Petr Flajsingr on 2018-12-07.
//

#ifndef PGR_PROJECT_COLLISIONBINS_H
#define PGR_PROJECT_COLLISIONBINS_H

#include <vector>
#include "CollisionObject.h"

namespace PGRsim::Collision {

struct CollisionBin {
  std::vector<CollisionObject *> objects;

  BoundingBox box;
};

class CollisionBins {
 protected:
  int xResolution, yResolution, zResolution;

  int binCount;

  BoundingBox area;

  CollisionBin *bins;

  std::vector<CollisionObject *> objects;
 public:
  CollisionBins(int xResolution, int yResolution, int zResolution, const BoundingBox &area);

  void addCollisionObject(CollisionObject *object);

  void recalculateBins(bool clearCalc = false);

  CollisionBin *getBins();

  int getXResolution() const;
  int getYResolution() const;
  int getZResolution() const;

  int getBinCount() const;

  virtual ~CollisionBins();
};
}

#endif //PGR_PROJECT_COLLISIONBINS_H
