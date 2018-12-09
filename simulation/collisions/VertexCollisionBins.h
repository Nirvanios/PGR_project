//
// Created by Petr Flajsingr on 2018-12-07.
//

#ifndef PGR_PROJECT_COLLISIONBINS_H
#define PGR_PROJECT_COLLISIONBINS_H

#include <vector>
#include "CollisionObject.h"
#include <SimVertex.h>

namespace PGRsim::Collision {

struct VertexCollisionBin {
  std::vector<SimVertex *> objects;

  RectArea box;
};

class VertexCollisionBins {
 protected:
  int xResolution, yResolution, zResolution;

  int binCount;

  RectArea area;

  VertexCollisionBin *bins;

  std::vector<SimVertex *> objects;
 public:
  VertexCollisionBins(int xResolution, int yResolution, int zResolution, const RectArea &area);

  void addCollisionObject(SimVertex *object);

  void recalculateBins(bool clearCalc = false);

  VertexCollisionBin *getBins();

  int getXResolution() const;
  int getYResolution() const;
  int getZResolution() const;

  int getBinCount() const;

  virtual ~VertexCollisionBins();
};
}

#endif //PGR_PROJECT_COLLISIONBINS_H
