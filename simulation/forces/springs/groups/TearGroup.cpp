//
// Created by Petr Flajsingr on 2018-12-12.
//

#include "TearGroup.h"

PGRsim::TearGroup::TearGroup(PGRsim::SimVertex *vertex,
                             PGRsim::ComplexObject *parent,
                             PGRsim::SnappableSpring *mainSpring,
                             PGRsim::TearOrientation orientation,
                             int width,
                             int height)
    : vertex(vertex), parent(parent), mainSpring(mainSpring), orientation(orientation), width(width), height(height) {}

void PGRsim::TearGroup::addSpring(PGRsim::Spring *spring) {
  springs.emplace_back(spring);
}

void PGRsim::TearGroup::addConstraint(PGRsim::LengthConstraint *constraint) {
  constraints.emplace_back(constraint);
}

PGRsim::SimVertex *PGRsim::TearGroup::check() {
  if (mainSpring->isSnapped()) {
    auto position = vertex->getCurrectPosition();
    auto newVertexIndex =
        dynamic_cast<PGRgraphics::ComplexGraphicsModel *>(parent->getObjectModel())->addVertex(position);

    auto newVertex = new SimVertex(
        vertex->getMass() / 2,
        Active,
        newVertexIndex,
        vertex->getCurrectPosition(),
        parent);
    parent->addVertex(newVertex);

    vertex->setMass(vertex->getMass() / 2);

    for (auto spring : springs) {
      spring->setSimulatedObjectA(newVertex);
    }

    for (auto constraint : constraints) {
      constraint->setSimulatedObjectA(newVertex);
    }

    for (auto constraint : constraintsToDestroy) {
      constraint->disable();
    }

    if (orientation == Vertical) {
      for (auto i = 0; i < parent->getObjectModel()->getVertexIndices().size(); i += 3) {
        int pos = -1;
        if (parent->getObjectModel()->getVertexIndices()[i] == vertex->getVertexId()) {
          pos = 0;
        }
        if (parent->getObjectModel()->getVertexIndices()[i + 1] == vertex->getVertexId()) {
          pos = 1;
        }
        if (parent->getObjectModel()->getVertexIndices()[i + 2] == vertex->getVertexId()) {
          pos = 2;
        }

        if (parent->getObjectModel()->getVertexIndices()[i] >= vertex->getVertexId()
            && parent->getObjectModel()->getVertexIndices()[i + 1] >= vertex->getVertexId()
            && parent->getObjectModel()->getVertexIndices()[i + 2] >= vertex->getVertexId()) {
          parent->getObjectModel()->getVertexIndices()[pos] = newVertexIndex;
        }
      }
    }

    return newVertex;
  }
  return nullptr;
}

void PGRsim::TearGroup::addConstraintToDestroy(PGRsim::LengthConstraint *constraint) {
  constraintsToDestroy.emplace_back(constraint);
}
