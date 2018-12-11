//
// Created by Petr Flajsingr on 2018-12-04.
//

#ifndef PGR_PROJECT_SNAPPABLESPRINGGROUP_H
#define PGR_PROJECT_SNAPPABLESPRINGGROUP_H

#include <vector>
#include <constraints/Constraint.h>
#include <ComplexObject.h>
#include "SnappableSpring.h"

namespace PGRsim {

/**
 * Group of constraints and snappable spring.
 * When any of the springs is snapped all constraints in the group are deactivated
 * and all springs are snapped.
 *
 * @author Petr Flajšingr
 */
class SnappableSpringGroup {
 private:
  std::vector<SnappableSpring *> springs;
  std::vector<Constraint *> constraints;

  int vertexID;

  ComplexObject *owner;

  bool snapped = false;

 protected:
  /**
   * Snap all springs and disable all constraints.
   */
  void snapAll();

 public:
  void addSpring(SnappableSpring *spring);

  void addConstraint(Constraint *constraint);

  /**
   * Check for snaps.
   * @return true if springs snapped, false otherwise
   */
  virtual bool check();

  void setVertexID(int id);

  int getVertexID();

  ComplexObject *getOwner() const;

  void setOwner(ComplexObject *owner);
};
}

#endif //PGR_PROJECT_SNAPPABLESPRINGGROUP_H
