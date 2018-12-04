//
// Created by Petr Flajsingr on 2018-12-04.
//

#ifndef PGR_PROJECT_SIMPLEGRAPHICSMODEL_H
#define PGR_PROJECT_SIMPLEGRAPHICSMODEL_H

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "GraphicsModel.h"

class SimpleGraphicsModel : public GraphicsModel {
 private:
  const glm::mat4 model = glm::mat4(1.f);
 protected:
  glm::vec3 position;
 public:
  static SimpleGraphicsModel* LoadFromOBJ(std::string path) {
    std::cout << "Loading object from: " << path << std::endl;
    auto model = new SimpleGraphicsModel();

    tinyobj::attrib_t attribs;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    if(!tinyobj::LoadObj(&attribs, &shapes, &materials, nullptr, nullptr, path.c_str())) {
      std::cerr << "Loading object failed" << std::endl;
      return nullptr;
    }

    model->indices = shapes[0].mesh.indices;

    for (auto indice : model->indices) {
      model->vertexIndices.emplace_back(indice.vertex_index);
      model->normalIndices.emplace_back(indice.normal_index);
    }

    for (int i = 0; i < attribs.vertices.size(); i += 3) {
      model->vertices.emplace_back(floatsToVec3(attribs.vertices[i], attribs.vertices[i + 1], attribs.vertices[i + 2]));
    }

    for (int i = 0; i < attribs.normals.size(); i += 3) {
      model->normals.emplace_back(floatsToVec3(attribs.normals[i], attribs.normals[i + 1], attribs.normals[i + 2]));
    }

    model->position = glm::vec3(0, 0, 0);

    return model;
  }

  glm::mat4 getTranslationMatrix() {
    return glm::translate(model, position);
  }
};

#endif //PGR_PROJECT_SIMPLEGRAPHICSMODEL_H
