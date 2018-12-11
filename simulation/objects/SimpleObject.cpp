//
// Created by Petr on 28.11.2018.
//

#include "SimpleObject.h"

PGRsim::SimpleObject::SimpleObject(float mass,
                                   PGRsim::SimObjectType objectType,
                                   PGRgraphics::SimpleGraphicsModel *model) : SimObjectWithModel(mass,
                                                                                                 objectType),
                                                                              model(model) {
  currentPosition = model->getPosition();

  previousPosition = currentPosition;
}

void PGRsim::SimpleObject::update(PGRsim::SimTime time) {
  model->setPosition(currentPosition);
}