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

  bool line = false;
 protected:
 public:
  SimpleGraphicsModel(const glm::vec3 &position, float *vertices, int verticesSize, unsigned char *indices, int indiciesSize)
      : position(position), verticesSize(verticesSize), indiciesSize(indiciesSize) {
        this->vertices = new float[verticesSize];
        memcpy(this->vertices, vertices, verticesSize * sizeof(float));
        this->indices = new unsigned char[indiciesSize];
        memcpy(this->indices, indices, indiciesSize * sizeof(unsigned char));
 }

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

 void setIsLine(bool isLine){
     this->line = isLine;
 }

 bool isLine(){
     return line;
 }
};

#endif //PGR_PROJECT_SIMPLEGRAPHICSMODEL_H
