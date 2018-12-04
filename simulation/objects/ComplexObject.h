//
// Created by Petr Flajsingr on 2018-12-03.
//

#ifndef PGR_PROJECT_COMPLEXOBJECT_H
#define PGR_PROJECT_COMPLEXOBJECT_H
#include <SimObject.h>
#include <collisions/CollisionObject.h>
#include <ComplexObject.h>
#include "Vertex.h"
#include "Constraint.h"
#include <vector>
#include <Spring.h>
#include <ComplexGraphicsModel.h>

namespace PGRsim {

class ComplexObject : public SimObject, Collision::CollisionObject {
 protected:
  PGRgraphics::ComplexGraphicsModel *model;
  std::vector<Vertex*> simVertices;

  std::vector<Constraint*> constraints;
  std::vector<Spring*> springs;

  void initVertices();

  void initConstraints();

  void initSprings();
 public:
  ComplexObject(float mass, PGRgraphics::ComplexGraphicsModel *model);

  PGRgraphics::ComplexGraphicsModel *getObjectModel() {
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
