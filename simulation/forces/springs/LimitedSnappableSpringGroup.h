//
// Created by Petr Flajsingr on 2018-12-04.
//

#ifndef PGR_PROJECT_LIMITEDSNAPPABLESPRINGGROUP_H
#define PGR_PROJECT_LIMITEDSNAPPABLESPRINGGROUP_H

#include "SnappableSpringGroup.h"

namespace PGRsim {

/**
 * Works the same as as SnappableSpringGroup but only snaps others springs when main spring is snapped.
 * @see SnappableSpringGroup
 */
class LimitedSnappableSpringGroup : public SnappableSpringGroup {
 private:
  SnappableSpring *mainSpring;
 public:
  explicit LimitedSnappableSpringGroup(SnappableSpring *mainSpring);

  bool check() override;
};
}
#endif //PGR_PROJECT_LIMITEDSNAPPABLESPRINGGROUP_H
