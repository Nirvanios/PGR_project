//
// Created by Petr Flajsingr on 2018-12-06.
//

#include <ComplexObject.h>
#include "CollisionDemoSimulation.h"

int width = 17, height = 17;

void PGRsim::CollisionDemoSimulation::prepareClothObject(std::string filePath) {
  auto clothObject = new ComplexObject(10.0f, Active, PGRgraphics::ComplexGraphicsModel::LoadFromOBJ(filePath));

  auto vertexIndices = clothObject->getObjectModel()->getVertexIndices();
  auto vertices = clothObject->getSimVertices();

  clothObject->addConstraint(glm::vec3(-0.034899, 0.999391, 1), 0);
  clothObject->addConstraint(glm::vec3(-0.034899, 0.999391, -1.000000), 272);

  float s = 8.0f, d = 0.1f;

  int index;
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      index = x * height + y;

      if (y < height - 1) {
        clothObject->addSpring(s, d, index, index + 1);
        clothObject->addConstraint(glm::distance(vertices[index]->getCurrectPosition(),
                                                 vertices[index + 1]->getCurrectPosition()),
                                   index,
                                   index + 1);

        if (x < width - 1) {
          clothObject->addSpring(s, d, index, index + 1);
          clothObject->addConstraint(glm::distance(vertices[index]->getCurrectPosition(),
                                                   vertices[index + width + 1]->getCurrectPosition()),
                                     index,
                                     index + width + 1);

          if (y > 0) {
            clothObject->addSpring(s, d, index, index + 1);
            clothObject->addConstraint(glm::distance(vertices[index]->getCurrectPosition(),
                                                     vertices[index + width + 1]->getCurrectPosition()),
                                       index,
                                       index + width - 1);
          }
        }
      }

      if (x < width - 1) {
        clothObject->addSpring(s, d, index, index + width);
        clothObject->addConstraint(glm::distance(vertices[index]->getCurrectPosition(),
                                                 vertices[index + width]->getCurrectPosition()),
                                   index,
                                   index + width);
      }

      if (y < height - 2) {
        clothObject->addSpring(s, d, index, index + 2);
        clothObject->addConstraint(glm::distance(vertices[index]->getCurrectPosition(),
                                                 vertices[index + 2]->getCurrectPosition()),
                                   index,
                                   index + 2);
      }

      if (x < width - 2) {
        clothObject->addSpring(s, d, index, index + 2 * width);
        clothObject->addConstraint(glm::distance(vertices[index]->getCurrectPosition(),
                                                 vertices[index + 2 * width]->getCurrectPosition()),
                                   index,
                                   index + 2 * width);
      }
    }
  }

  for (auto constr : clothObject->getConstraints()) {
    addConstraint(constr);
  }

  for (auto spring : clothObject->getSprings()) {
    addSpring(spring);
  }

  for (auto simVertex : clothObject->getSimVertices()) {
    addObject(simVertex);
  }

  addObject(clothObject);
}

void PGRsim::CollisionDemoSimulation::update(PGRsim::SimTime time) {
  for (auto group : groups) {
    if (group->check()) {
      group->getOwner()->removeIndices(group->getVertexID());
      objects.erase(std::find(objects.begin(),
                              objects.end(),
                              group->getOwner()->getSimVertices()[group->getVertexID()]));
    }
  }

  PGRsim::Simulation::update(time);
}

void PGRsim::CollisionDemoSimulation::tear() {
  for (auto constraint : tearDemoLeft) {
    constraint->setPosition(constraint->getPosition() - glm::vec3(0.01f));
  }

  for (auto constraint : tearDemoRight) {
    constraint->setPosition(constraint->getPosition() + glm::vec3(0.01f));
  }
}

void PGRsim::CollisionDemoSimulation::stopTearDemo() {
  for (auto constraint : tearDemoLeft) {
    constraint->disable();
  }

  for (auto constraint : tearDemoRight) {
    constraint->disable();
  }
}

void PGRsim::CollisionDemoSimulation::deleteDemoConstraints() {

}
