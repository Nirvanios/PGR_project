//
// Created by Petr Flajsingr on 2018-12-07.
//

#ifndef PGR_PROJECT_COLLISIONBINS_H
#define PGR_PROJECT_COLLISIONBINS_H

#include <vector>
#include "CollisionObject.h"
#include <SimVertex.h>

namespace PGRsim::Collision {

/**
 * Part of a space defined by axis aligned rectangular area.
 * Contains list of objects in this area.
 *
 * @author Petr Flajšingr
 */
struct VertexCollisionBin {
  std::vector<SimVertex *> objects;

  RectArea box;
};

/**
 * Container and builder of bins dividing a space.
 *
 * Divides the space into amount of parts defined in a constructor.
 *
 * @author Petr Flajšingr
 */
class VertexCollisionBins {
 protected:
  int xResolution, yResolution, zResolution;

  int binCount;

  RectArea area;

  VertexCollisionBin *bins;

  std::vector<SimVertex *> objects;
 public:
  /**
   * Create and initialize collision bins.
   * @param xResolution amount of bins in X axis
   * @param yResolution amount of bins in Y axis
   * @param zResolution amount of bins in Z axis
   * @param area divided area
   */
  VertexCollisionBins(int xResolution, int yResolution, int zResolution, const RectArea &area);

  /**
   * Add collision object to divide into bins later on.
   * @param object
   */
  void addCollisionObject(SimVertex *object);

  /**
   * Recalculate positions of objects in bins.
   * @param clearCalc __UNUSED__
   */
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
