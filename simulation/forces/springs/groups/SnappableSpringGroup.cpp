//
// Created by Petr Flajsingr on 2018-12-04.
//

#include "SnappableSpringGroup.h"

void PGRsim::SnappableSpringGroup::snapAll() {
  for (auto spring : springs) {
    spring->snapped = true;
  }

  for (auto constraint : constraints) {
    constraint->disable();
  }
}

void PGRsim::SnappableSpringGroup::addSpring(PGRsim::SnappableSpring *spring) {
  springs.emplace_back(spring);
}

bool PGRsim::SnappableSpringGroup::check() {
  if (snapped) {
    return false;
  }
  if (std::any_of(springs.begin(),
                  springs.end(),
                  [](auto spring) {
                    return spring->snapped;
                  })) {
    snapAll();
    snapped = true;
    return true;
  }

  return false;
}
void PGRsim::SnappableSpringGroup::addConstraint(PGRsim::Constraint *constraint) {
  constraints.emplace_back(constraint);
}
PGRsim::ComplexObject *PGRsim::SnappableSpringGroup::getOwner() const {
  return owner;
}
void PGRsim::SnappableSpringGroup::setOwner(PGRsim::ComplexObject *owner) {
  SnappableSpringGroup::owner = owner;
}
void PGRsim::SnappableSpringGroup::setVertexID(int id) {
  vertexID = id;
}
int PGRsim::SnappableSpringGroup::getVertexID() {
  return vertexID;
}

PGRsim::SnappableSpringGroup::~SnappableSpringGroup() = default;
