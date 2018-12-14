//
// Created by Petr Flajsingr on 2018-12-12.
//

#include "TearGroup.h"

PGRsim::TearGroup::TearGroup(PGRsim::SimVertex *vertex,
                             PGRsim::SnappableSpring *mainSpring,
                             PGRsim::TearOrientation orientation)
    : vertex(vertex), mainSpring(mainSpring), orientation(orientation) {}

void PGRsim::TearGroup::addSpring(PGRsim::Spring *spring) {
  springs.emplace_back(spring);
}

void PGRsim::TearGroup::addConstraint(PGRsim::DistanceConstraint *constraint) {
  constraints.emplace_back(constraint);
}

PGRsim::SimVertex *PGRsim::TearGroup::check() {
  if (!torn && mainSpring->isSnapped()) {
    torn = true;
    auto position = vertex->getCurrectPosition();
    auto newVertexIndex =
        dynamic_cast<PGRgraphics::ComplexGraphicsModel *>(vertex->getParent()->getObjectModel())->addVertex(position);

    auto newVertex = new SimVertex(
        vertex->getMass() / 2,
        Active,
        newVertexIndex,
        vertex->getCurrectPosition(),
        vertex->getParent());
    vertex->getParent()->addVertex(newVertex);

    vertex->setMass(vertex->getMass() / 2);

    for (auto spring : springs) {
      if (spring->getSimulatedObjectA() == vertex) {
        spring->setSimulatedObjectA(newVertex);
      } else {
        spring->setSimulatedObjectB(newVertex);
      }
    }

    for (auto constraint : constraints) {
      constraint->setSimulatedObjectA(newVertex);

      if (constraint->getObjectA() == vertex) {
        constraint->setSimulatedObjectA(newVertex);
      } else {
        constraint->setSimulatedObjectB(newVertex);
      }
    }

    for (auto constraint : constraintsToDestroy) {
      constraint->disable();
    }

    if (orientation == Vertical) {
      for (auto i = 0; i < vertex->getParent()->getObjectModel()->getVertexIndices().size(); i += 3) {
        int pos = -1;
        if (vertex->getParent()->getObjectModel()->getVertexIndices()[i] == vertex->getVertexId()) {
          pos = 0;
        }
        if (vertex->getParent()->getObjectModel()->getVertexIndices()[i + 1] == vertex->getVertexId()) {
          pos = 1;
        }
        if (vertex->getParent()->getObjectModel()->getVertexIndices()[i + 2] == vertex->getVertexId()) {
          pos = 2;
        }

        if (pos == -1) {
          continue;
        }

        if (vertex->getParent()->getObjectModel()->getVertexIndices()[i] >= vertex->getVertexId()
            && vertex->getParent()->getObjectModel()->getVertexIndices()[i + 1] >= vertex->getVertexId()
            && vertex->getParent()->getObjectModel()->getVertexIndices()[i + 2] >= vertex->getVertexId()) {
          vertex->getParent()->getObjectModel()->getVertexIndices()[i + pos] = newVertexIndex;
        }
      }
    }

    if (orientation == Horizontal) {
      for (auto i = 0; i < vertex->getParent()->getObjectModel()->getVertexIndices().size(); i += 3) {
        int pos = -1;
        if (vertex->getParent()->getObjectModel()->getVertexIndices()[i] == vertex->getVertexId()) {
          pos = 0;
        }
        if (vertex->getParent()->getObjectModel()->getVertexIndices()[i + 1] == vertex->getVertexId()) {
          pos = 1;
        }
        if (vertex->getParent()->getObjectModel()->getVertexIndices()[i + 2] == vertex->getVertexId()) {
          pos = 2;
        }

        if (pos == -1) {
          continue;
        }

        int biggerCount = 0;
        if (vertex->getParent()->getObjectModel()->getVertexIndices()[i] >= vertex->getVertexId()) {
          biggerCount++;
        }
        if (vertex->getParent()->getObjectModel()->getVertexIndices()[i + 1] >= vertex->getVertexId()) {
          biggerCount++;
        }
        if (vertex->getParent()->getObjectModel()->getVertexIndices()[i + 2] >= vertex->getVertexId()) {
          biggerCount++;
        }
        if (biggerCount >= 2) {
          vertex->getParent()->getObjectModel()->getVertexIndices()[i + pos] = newVertexIndex;
        }
      }
    }

    return newVertex;
  }
  return nullptr;
}

void PGRsim::TearGroup::addConstraintToDestroy(PGRsim::DistanceConstraint *constraint) {
  constraintsToDestroy.emplace_back(constraint);
}
