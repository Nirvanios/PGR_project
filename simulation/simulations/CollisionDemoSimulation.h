//
// Created by Petr Flajsingr on 2018-12-06.
//

#ifndef PGR_PROJECT_CLOTHSIM_H
#define PGR_PROJECT_CLOTHSIM_H

#include <Simulation.h>
#include <springs/groups/LimitedSnappableSpringGroup.h>
#include <constraints/PositionConstraint.h>
#include <vector>


namespace PGRsim {

/**
 * Demo cloth simulation.
 *
 * Adds collision detection.
 */
class CollisionDemoSimulation : public Simulation {
 private:
  Collision::VertexCollisionChecker collisionChecker;
 public:

  void prepareClothObject(std::string filePath, std::string texPath = "");

  void update(SimTime time) override;

  void addObject(SimObject *object) override;
};
}

#endif //PGR_PROJECT_CLOTHSIM_H
