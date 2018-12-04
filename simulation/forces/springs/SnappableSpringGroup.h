//
// Created by Petr Flajsingr on 2018-12-04.
//

#ifndef PGR_PROJECT_SNAPPABLESPRINGGROUP_H
#define PGR_PROJECT_SNAPPABLESPRINGGROUP_H

#include <vector>
#include "SnappableSpring.h"

namespace PGRsim {
class SnappableSpringGroup {
 private:
  std::vector<SnappableSpring *> springs;

  void snapAll();
 public:
  void addSpring(SnappableSpring *spring);

  bool checkSnaps();
};
}

#endif //PGR_PROJECT_SNAPPABLESPRINGGROUP_H
