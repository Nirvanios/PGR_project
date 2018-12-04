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

 protected:
  void snapAll();

 public:
  void addSpring(SnappableSpring *spring);

  virtual bool check();
};
}

#endif //PGR_PROJECT_SNAPPABLESPRINGGROUP_H
