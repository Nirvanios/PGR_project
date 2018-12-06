//
// Created by Petr Flajsingr on 2018-12-06.
//

#include <ComplexObject.h>
#include "ClothSim.h"
void PGRsim::ClothSim::addObject(PGRsim::SimObject *object) {
  auto complexObj = dynamic_cast<ComplexObject *>(object);
  if (complexObj != nullptr) {
    complexObj->initSprings(0.8f, 0.1f);
  }

  Simulation::addObject(object);
}
