//
// Created by Petr Flajsingr on 2018-12-06.
//

#ifndef PGR_PROJECT_SIMOBJECTWITHMODEL_H
#define PGR_PROJECT_SIMOBJECTWITHMODEL_H

#include <objects/GraphicsModel.h>
#include "SimObject.h"

namespace PGRsim {

/**
 * Simulated object with a graphics model that can be rendered on screen.
 *
 * @author Petr Flajšingr
 */
class SimObjectWithModel : public SimObject {
 public:
  SimObjectWithModel(float mass, SimObjectType type) : SimObject(mass, type) {}

  virtual PGRgraphics::GraphicsModel *getObjectModel() = 0;
};
}

#endif //PGR_PROJECT_SIMOBJECTWITHMODEL_H
