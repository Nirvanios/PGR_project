//
// Created by Petr Flajsingr on 2018-12-01.
//

#ifndef PGR_PROJECT_SIMPLEGRAPHICSMODEL_H
#define PGR_PROJECT_SIMPLEGRAPHICSMODEL_H

#include <glm/glm.hpp>
class SimpleGraphicsModel {
 private:
  glm::vec3 position;

  float* vertices;

  float* indices;
 protected:
 public:
  SimpleGraphicsModel(const glm::vec3 &position, float *vertices, float *indices)
      : position(position), vertices(vertices), indices(indices) {}

  void setPosition(glm::vec3 position) {
    this->position = position;
  }

  glm::vec3 getPosition() {
    return position;
  }
};

#endif //PGR_PROJECT_SIMPLEGRAPHICSMODEL_H
