//
// Created by Petr Flajsingr on 2018-12-06.
//

#ifndef PGR_PROJECT_FLOORFORCE_H
#define PGR_PROJECT_FLOORFORCE_H

#include <ForceGenerator.h>

namespace PGRsim {

enum Direction {
  Xplus, Xminus, Yplus, Yminus, Zplus, Zminus
};

class LocationLimit : public ForceGenerator {
 private:
  float coordLimit;
  Direction dir;
 public:
  LocationLimit(float coordLimit, Direction dir);
  void applyForce(SimObject &object) override;
};
}
#endif //PGR_PROJECT_FLOORFORCE_H
