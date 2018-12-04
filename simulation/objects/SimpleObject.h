//
// Created by Petr on 28.11.2018.
//

#ifndef PGR_PROJECT_SIMULATEDMODEL_H
#define PGR_PROJECT_SIMULATEDMODEL_H

#include <collisions/CollisionObject.h>
#include "DEPRECATED_SimpleGraphicsModel.h"
#include "SimpleObject.h"

namespace PGRsim {

/**
 * Simulated object with unchangeable shape.
 *
 * Position may be used to create translation matrix for model's vertices.
 */
 class SimpleObject : public SimObject, Collision::CollisionObject {
  protected:
  DEPRECATED_SimpleGraphicsModel *model;
 public:
  SimpleObject(float mass, SimObjectType objectType, DEPRECATED_SimpleGraphicsModel *model);

  void setObjectModel(DEPRECATED_SimpleGraphicsModel *model) {
    this->model = model;
  }

  DEPRECATED_SimpleGraphicsModel *getObjectModel() {
    return model;
  }

  void update(SimTime time) override;

  void calcBoundingBox() override;

  Collision::BoundingBox getBoundingBox() override;
 };
}

#endif //PGR_PROJECT_SIMULATEDMODEL_H
