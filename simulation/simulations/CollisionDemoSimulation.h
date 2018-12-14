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
 *
 * @author Petr Flajšingr
 */
class CollisionDemoSimulation : public Simulation {
 private:
  Collision::VertexCollisionChecker collisionChecker;
 public:

  /**
   * Connect cloths springs a constraints.
   * @param filePath path to model file
   * @param texPath path to texture file
   */
  void prepareClothObject(std::string filePath, std::string texPath = "");

  /**
   * Update simulation
   * @param time
   */
  void update(SimTime time) override;

  void addObject(SimObject *object) override;
};
}

#endif //PGR_PROJECT_CLOTHSIM_H
