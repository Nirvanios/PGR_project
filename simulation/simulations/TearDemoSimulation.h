//
// Created by Petr Flajsingr on 2018-12-11.
//

#ifndef PGR_PROJECT_TEARDEMOSIMULATION_H
#define PGR_PROJECT_TEARDEMOSIMULATION_H

#include "Simulation.h"
#include <springs/SnappableSpringGroup.h>

namespace PGRsim {

class TearDemoSimulation : public Simulation {
 private:
  std::vector<PointConstraint *> tearDemoLeft;
  std::vector<PointConstraint *> tearDemoRight;

  std::vector<SnappableSpringGroup *> groups;
 public:
  void prepareClothObject(std::string filePath);

  void tear();

  void stopTearDemo();

  void update(SimTime time) override;
};
}

#endif //PGR_PROJECT_TEARDEMOSIMULATION_H
