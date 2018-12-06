//
// Created by Petr Flajsingr on 2018-12-04.
//

#include <StdoutLogger.h>
#include "LimitedSnappableSpringGroup.h"
PGRsim::LimitedSnappableSpringGroup::LimitedSnappableSpringGroup(PGRsim::SnappableSpring *mainSpring) : mainSpring(
    mainSpring) {}
bool PGRsim::LimitedSnappableSpringGroup::check() {
  if (mainSpring->isSnapped()) {
    SnappableSpringGroup::snapAll();
    return true;
  }
  return false;
}
