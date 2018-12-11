//
// Created by Petr on 28.11.2018.
//

#ifndef PGR_PROJECT_SIMULATEDMODEL_H
#define PGR_PROJECT_SIMULATEDMODEL_H

#include <collisions/CollisionObject.h>
#include "SimpleObject.h"
#include <SimObject.h>
#include <SimpleGraphicsModel.h>
#include <SimObjectWithModel.h>

namespace PGRsim {

/**
 * Simulated object with unchangeable shape.
 *
 * Position may be used to create translation matrix for model's vertices.
 *
 * @author Petr Flajšingr
 */
class SimpleObject : public SimObjectWithModel {
 protected:
  PGRgraphics::SimpleGraphicsModel *model;
 public:
  SimpleObject(float mass, SimObjectType objectType, PGRgraphics::SimpleGraphicsModel *model);

  void setObjectModel(PGRgraphics::SimpleGraphicsModel *model) {
    this->model = model;
  }

  PGRgraphics::GraphicsModel *getObjectModel() override {
    return model;
  }

  void update(SimTime time) override;
};
}

#endif //PGR_PROJECT_SIMULATEDMODEL_H
