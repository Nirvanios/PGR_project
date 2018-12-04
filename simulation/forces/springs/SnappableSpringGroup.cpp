//
// Created by Petr Flajsingr on 2018-12-04.
//

#include "SnappableSpringGroup.h"

void PGRsim::SnappableSpringGroup::snapAll() {
  for (auto spring : springs) {
    spring->snapped = true;
  }
}
void PGRsim::SnappableSpringGroup::addSpring(PGRsim::SnappableSpring *spring) {
  springs.emplace_back(spring);
}
bool PGRsim::SnappableSpringGroup::checkSnaps() {
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
