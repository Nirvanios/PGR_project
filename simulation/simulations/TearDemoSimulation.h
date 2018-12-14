//
// Created by Petr Flajsingr on 2018-12-11.
//

#ifndef PGR_PROJECT_TEARDEMOSIMULATION_H
#define PGR_PROJECT_TEARDEMOSIMULATION_H

#include "Simulation.h"
#include <springs/groups/SnappableSpringGroup.h>

namespace PGRsim {

class TearDemoSimulation : public Simulation {
 private:
  std::vector<PositionConstraint *> tearDemoLeft;
  std::vector<PositionConstraint *> tearDemoRight;

  std::vector<SnappableSpringGroup *> groups;
 public:
  virtual ~TearDemoSimulation();

  void prepareClothObject(std::string filePath);

  void tear();

  void stopTearDemo();

  void update(SimTime time) override;
};
}

#endif //PGR_PROJECT_TEARDEMOSIMULATION_H
