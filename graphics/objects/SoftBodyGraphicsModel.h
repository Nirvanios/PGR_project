//
// Created by kuro on 2.12.18.
//

#ifndef PGR_PROJECT_SOFTBODYGRAPHICSMODEL_H
#define PGR_PROJECT_SOFTBODYGRAPHICSMODEL_H



class SoftBodyGraphicsModel {
private:
    float * vertices;
    int verticesSize;

    uint8_t indicies;
    int indiciesSize;

public:
    SoftBodyGraphicsModel(float *vertices, int verticesSize, uint8_t indicies, int indiciesSize) :
            vertices(vertices) ,verticesSize(verticesSize), indicies(indicies), indiciesSize(indiciesSize){
    }

  float *getVertices() const {
      return vertices;
  }
  void setVertices(float *vertices) {
      SoftBodyGraphicsModel::vertices = vertices;
  }
  int getVerticesSize() const {
      return verticesSize;
  }
  void setVerticesSize(int verticesSize) {
      SoftBodyGraphicsModel::verticesSize = verticesSize;
  }
  uint8_t getIndicies() const {
      return indicies;
  }
  void setIndicies(uint8_t indicies) {
      SoftBodyGraphicsModel::indicies = indicies;
  }
  int getIndiciesSize() const {
      return indiciesSize;
  }
  void setIndiciesSize(int indiciesSize) {
      SoftBodyGraphicsModel::indiciesSize = indiciesSize;
  }
};


#endif //PGR_PROJECT_SOFTBODYGRAPHICSMODEL_H
