//
// Created by Petr Flajsingr on 2018-12-07.
//

#include "ShapedComplexObject.h"

PGRsim::ShapedComplexObject::ShapedComplexObject(float mass,
                                                 PGRsim::SimObjectType type,
                                                 PGRgraphics::ComplexGraphicsModel *model) : ComplexObject(mass,
                                                                                                           type,
                                                                                                           model) {
  shape = this->clone(Passive);

  for (auto index : shape->getObjectModel()->getVertexIndices()) {
    addShapeSpring(2.0f, 0.2f, index);
  }
}

void PGRsim::ShapedComplexObject::addShapeSpring(float stiffness, float damping, int vertexID) {
  shapeSprings.emplace_back(new Spring(stiffness,
                                       damping,
                                       shape->getSimVertices()[vertexID],
                                       getSimVertices()[vertexID]));
}

void PGRsim::ShapedComplexObject::addShapeLengthConstraint(float length, int vertexID) {
  shapeConstraints.emplace_back(new LengthConstraint(shape->getSimVertices()[vertexID],
                                                     getSimVertices()[vertexID],
                                                     length));
}

void PGRsim::ShapedComplexObject::addShapePointConstraint(glm::vec3 position, int vertexID) {
  shapeConstraints.emplace_back(new PointConstraint(position, shape->getSimVertices()[vertexID]));

  shapeConstraints.emplace_back(new PointConstraint(position, > getSimVertices()[vertexID]));
}

const std::vector<PGRsim::Spring *> &PGRsim::ShapedComplexObject::getShapeSprings() const {
  return shapeSprings;
}

const std::vector<PGRsim::Constraint *> &PGRsim::ShapedComplexObject::getShapeConstraints() const {
  return shapeConstraints;
}

