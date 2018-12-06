//
// Created by Petr Flajsingr on 2018-12-06.
//

#include <ComplexObject.h>
#include "ClothSim.h"

const int width = 17, height = 17;

void PGRsim::ClothSim::prepareClothObject(std::string filePath) {
  auto clothObject = new ComplexObject(1.0f, PGRgraphics::ComplexGraphicsModel::LoadFromOBJ(filePath));

  auto vertexIndices = clothObject->getObjectModel()->getVertexIndices();
  auto vertices = clothObject->getSimVertices();

  clothObject->addConstraint(glm::vec3(-0.034899, 0.999391, 1), 0);
  clothObject->addConstraint(glm::vec3(-0.034899, 0.999391, -1.000000), 272);
  /*
  clothObject->addConstraint(glm::vec3(-4.37113, 4.24692, 0), 0);
  clothObject->addConstraint(glm::vec3(4.12272, 4.24692, 0), 4160);
  clothObject->addConstraint(glm::vec3(-1.8437, 4.42987, 0.000000), 1300);
  clothObject->addConstraint(glm::vec3(2.04713, 4.47515, 0.000000), 3120);*/

  float s = 4.0f, d = 2.0f;

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
