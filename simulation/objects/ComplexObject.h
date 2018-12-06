//
// Created by Petr Flajsingr on 2018-12-03.
//

#ifndef PGR_PROJECT_COMPLEXOBJECT_H
#define PGR_PROJECT_COMPLEXOBJECT_H
#include <SimObject.h>
#include <collisions/CollisionObject.h>
#include <ComplexObject.h>
#include "SimVertex.h"
#include "constraints/Constraint.h"
#include "constraints/PointConstraint.h"
#include "constraints/LengthConstraint.h"
#include <vector>
#include <springs/Spring.h>
#include <ComplexGraphicsModel.h>
#include <SimObjectWithModel.h>

namespace PGRsim {

class ComplexObject : public SimObjectWithModel, public Collision::CollisionObject {
 protected:
  PGRgraphics::ComplexGraphicsModel *model;
  std::vector<SimVertex *> simVertices;

  std::vector<Constraint*> constraints;
  std::vector<Spring*> springs;
 public:
  ComplexObject(float mass, PGRgraphics::ComplexGraphicsModel *model);

  PGRgraphics::GraphicsModel *getObjectModel() override {
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

  void initSprings(float stiffness, float damping);

  void addSpring(float stiffness, float damping, int vertexID1, int vertexID2);

  void addConstraint(const glm::vec3 &position, int vertexID);

  void addConstraint(float length, int vertexID1, int vertexID2);

  const std::vector<SimVertex *> &getSimVertices() {
    return simVertices;
  }

  void recalcNormals();
};
}

#endif //PGR_PROJECT_COMPLEXOBJECT_H
