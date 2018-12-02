//
// Created by Petr Flajsingr on 2018-12-01.
//

#ifndef PGR_PROJECT_SIMPLEGRAPHICSMODEL_H
#define PGR_PROJECT_SIMPLEGRAPHICSMODEL_H

#include <glm/glm.hpp>
class SimpleGraphicsModel {
 private:
  glm::vec3 position;

  float *vertices;
  int verticesSize;

  unsigned char *indices;
  int indiciesSize;
 protected:
 public:
  SimpleGraphicsModel(const glm::vec3 &position, float *vertices, int verticesSize, unsigned char *indices, int indiciesSize)
      : position(position), vertices(vertices), verticesSize(verticesSize), indices(indices), indiciesSize(verticesSize) {}

  void setPosition(glm::vec3 position) {
    this->position = position;
  }

  glm::vec3 getPosition() {
    return position;
  }

  float *getVertices() {
   return vertices;
  }

  int getVerticesSize(){
     return verticesSize;
 }

  unsigned char *getIndices() {
    return indices;
 }

 int getIndiciesSize(){
     return indiciesSize;
 }
};

#endif //PGR_PROJECT_SIMPLEGRAPHICSMODEL_H
