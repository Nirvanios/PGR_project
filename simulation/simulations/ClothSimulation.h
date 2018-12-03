//
// Created by Petr Flajsingr on 2018-12-01.
//

#ifndef PGR_PROJECT_CLOTHSIMULATION_H
#define PGR_PROJECT_CLOTHSIMULATION_H

#include "SoftBodySimulation.h"

namespace PGRsim {
class ClothSimulation : public SoftBodySimulation {
 private:
  void createVertices(float mass);

  void connectSprings(float structStiffness, float structDamping,
                      float shearStiffness, float shearDamping,
                      float bendStiffness, float bendDamping);
 protected:
 public:
  ClothSimulation(float mass, float structStiffness, float structDamping,
                  float shearStiffness, float shearDamping,
                  float bendStiffness, float bendDamping);

  void update(SimTime time) override;
};
}

#endif //PGR_PROJECT_CLOTHSIMULATION_H
