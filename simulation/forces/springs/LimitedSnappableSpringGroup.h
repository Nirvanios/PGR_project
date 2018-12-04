//
// Created by Petr Flajsingr on 2018-12-04.
//

#ifndef PGR_PROJECT_LIMITEDSNAPPABLESPRINGGROUP_H
#define PGR_PROJECT_LIMITEDSNAPPABLESPRINGGROUP_H

#include "SnappableSpringGroup.h"

namespace PGRsim {

class LimitedSnappableSpringGroup : public SnappableSpringGroup {
 private:
  SnappableSpring *mainSpring;
 public:
  explicit LimitedSnappableSpringGroup(SnappableSpring *mainSpring);

  bool check() override;
};
}
#endif //PGR_PROJECT_LIMITEDSNAPPABLESPRINGGROUP_H
