//
// Created by Petr Flajsingr on 2018-12-03.
//

#ifndef PGR_PROJECT_COMPLEXOBJECT_H
#define PGR_PROJECT_COMPLEXOBJECT_H
#include <SimObject.h>
#include <collisions/CollisionObject.h>
#include <objects/DEPRECATED_SoftBodyGraphicsModel.h>
#include "Vertex.h"
#include "Constraint.h"
#include <vector>
#include <Spring.h>

namespace PGRsim {

class ComplexObject : public SimObject, Collision::CollisionObject {
 protected:
  DEPRECATED_SoftBodyGraphicsModel* model;
  std::vector<Vertex*> simVertices;

  std::vector<Constraint*> constraints;
  std::vector<Spring*> springs;

  void initVertices();

  void initConstraints();

  void initSprings();
 public:
  ComplexObject(float mass, DEPRECATED_SoftBodyGraphicsModel *model);

  DEPRECATED_SoftBodyGraphicsModel *getObjectModel() {
    return model;
  }

  const std::vector<Constraint*> &getConstraints() {
    return constraints;
  }

  const std::vector<Spring*> &getSprings() {
    return springs;
  }

  void update(SimTime time) override;

  void calcBoundingBox() override;
};
}

#endif //PGR_PROJECT_COMPLEXOBJECT_H
