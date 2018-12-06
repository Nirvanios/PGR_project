//
// Created by Petr Flajsingr on 2018-12-06.
//

#ifndef PGR_PROJECT_CLOTHSIM_H
#define PGR_PROJECT_CLOTHSIM_H

#include <Simulation.h>

namespace PGRsim {

class ClothSim : public Simulation {
 private:
 public:
  void prepareClothObject(std::string filePath);
};
}

#endif //PGR_PROJECT_CLOTHSIM_H
