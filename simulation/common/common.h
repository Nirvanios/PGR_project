//
// Created by Petr on 28.11.2018.
//

#ifndef PGR_PROJECT_COMMON_H
#define PGR_PROJECT_COMMON_H

typedef float SimulationTime;

class GraphicsSimpleObject {
 private:
  glm::vec3 position;

  float* vertices;

  float* indices;
 protected:
 public:
  GraphicsSimpleObject(const glm::vec3 &position, float *vertices, float *indices)
      : position(position), vertices(vertices), indices(indices) {}

  void setPosition(glm::vec3 position) {
   this->position = position;
 }

 glm::vec3 getPosition() {
   return position;
 }
};

#endif //PGR_PROJECT_COMMON_H
