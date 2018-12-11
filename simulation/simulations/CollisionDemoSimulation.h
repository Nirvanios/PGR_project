//
// Created by Petr Flajsingr on 2018-12-06.
//

#ifndef PGR_PROJECT_CLOTHSIM_H
#define PGR_PROJECT_CLOTHSIM_H

#include <Simulation.h>
#include <springs/LimitedSnappableSpringGroup.h>
#include <constraints/PointConstraint.h>
#include <vector>


namespace PGRsim {

/**
 * Demo cloth simulation.
 *
 * Adds collision detection.
 */
class CollisionDemoSimulation : public Simulation {
 private:
 public:
  void prepareClothObject(std::string filePath);

  void update(SimTime time) override;
};
}

#endif //PGR_PROJECT_CLOTHSIM_H
