//
// Created by Petr Flajsingr on 2018-12-06.
//

#include <StdoutLogger.h>
#include "LocationLimit.h"

void PGRsim::LocationLimit::applyForce(PGRsim::SimObject &object) {
  auto objectpos = object.getCurrectPosition();
  switch (dir) {
    case Xplus:
      if (objectpos.x < coordLimit) {
        object.setCurrentPosition(glm::vec3(coordLimit, objectpos.y, objectpos.z));
      }
      break;
    case Xminus:
      if (objectpos.x > coordLimit) {
        object.setCurrentPosition(glm::vec3(coordLimit, objectpos.y, objectpos.z));
      }
      break;
    case Yplus:
      if (objectpos.y < coordLimit) {
        object.setCurrentPosition(glm::vec3(objectpos.x, coordLimit, objectpos.z));
      }
      break;
    case Yminus:
      if (objectpos.y > coordLimit) {
        object.setCurrentPosition(glm::vec3(objectpos.x, coordLimit, objectpos.z));
      }
      break;
    case Zplus:
      if (objectpos.z < coordLimit) {
        object.setCurrentPosition(glm::vec3(objectpos.x, objectpos.y, coordLimit));
      }
      break;
    case Zminus:
      if (objectpos.z > coordLimit) {
        object.setCurrentPosition(glm::vec3(objectpos.x, objectpos.y, coordLimit));
      }
      break;
  }
}
PGRsim::LocationLimit::LocationLimit(float coordLimit, PGRsim::Direction dir) : coordLimit(coordLimit), dir(dir) {}
