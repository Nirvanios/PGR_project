//
// Created by Petr Flajsingr on 2018-12-04.
//

#include "SnappableSpringGroup.h"
#include <algorithm>

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
  if (std::any_of(springs.begin(),
                  springs.end(),
                  [](auto spring) {
                    return spring->snapped;
                  })) {
    snapAll();
    return true;
  }
  return false;
}
void PGRsim::SnappableSpringGroup::addConstraint(PGRsim::Constraint *constraint) {
  constraints.emplace_back(constraint);
}
