//
// Created by Petr Flajsingr on 2018-12-07.
//

#ifndef PGR_PROJECT_SHAPEDCOMPLEXOBJECT_H
#define PGR_PROJECT_SHAPEDCOMPLEXOBJECT_H

#include "ComplexObject.h"
namespace PGRsim {

/**
 * Object which is trying to hold its shape by being connected to an unchanging invisible shape.
 *
 * _____ NOT FINISHED _____
 */
class ShapedComplexObject : public ComplexObject {
 protected:
  ComplexObject *shape;
  std::vector<Spring *> shapeSprings;
  std::vector<Constraint *> shapeConstraints;

  void addShapeSpring(float stiffness, float damping, int vertexID);

  void addShapePointConstraint(glm::vec3 position, int vertexID);

  void addShapeLengthConstraint(float length, int vertexID);
 public:
  ShapedComplexObject(float mass, SimObjectType type, PGRgraphics::ComplexGraphicsModel *model);

  const std::vector<Spring *> &getShapeSprings() const;

  const std::vector<Constraint *> &getShapeConstraints() const;

  ComplexObject *getShape() const;
};
}

#endif //PGR_PROJECT_SHAPEDCOMPLEXOBJECT_H
