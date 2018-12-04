//
// Created by Petr on 28.11.2018.
//

#ifndef PGR_PROJECT_SIMULATEDMODEL_H
#define PGR_PROJECT_SIMULATEDMODEL_H

#include <collisions/CollisionObject.h>
#include "SimpleObject.h"
#include <SimObject.h>
#include <SimpleGraphicsModel.h>

namespace PGRsim {

/**
 * Simulated object with unchangeable shape.
 *
 * Position may be used to create translation matrix for model's vertices.
 */
 class SimpleObject : public SimObject, Collision::CollisionObject {
  protected:
  SimpleGraphicsModel *model;
 public:
  SimpleObject(float mass, SimObjectType objectType, SimpleGraphicsModel *model);

  void setObjectModel(SimpleGraphicsModel *model) {
    this->model = model;
  }

  SimpleGraphicsModel *getObjectModel() {
    return model;
  }

  void update(SimTime time) override;

  void calcBoundingBox() override;

  Collision::BoundingBox getBoundingBox() override;
 };
}

#endif //PGR_PROJECT_SIMULATEDMODEL_H
