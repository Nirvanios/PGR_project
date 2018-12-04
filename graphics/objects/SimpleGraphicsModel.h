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

    std::string error;
    if(!tinyobj::LoadObj(&attribs, &shapes, &materials, nullptr, &error, path.c_str())) {
      std::cerr << "Loading object failed: " + error << std::endl;
      return nullptr;
    }

    model->indices = shapes[0].mesh.indices;


    model->normals.resize(attribs.vertices.size());

    std::for_each(model->normals.begin(), model->normals.end(),
        [] (glm::vec3& value) {
      value = glm::vec3(0.0f);
    });



    for (auto indice : model->indices) {
      model->vertexIndices.emplace_back(indice.vertex_index);
      //model->normals.emplace_back(attribs.normals[indice.normal_index]);
      model->normals[indice.vertex_index] += glm::vec3(attribs.normals[indice.normal_index * 3],
                                                       attribs.normals[indice.normal_index * 3 + 1],
                                                       attribs.normals[indice.normal_index * 3 + 2]);
    }

    std::for_each(model->normals.begin(), model->normals.end(),
                  [] (glm::vec3& value) {
                    value = glm::normalize(value);
                  });



    for (int i = 0; i < attribs.vertices.size(); i += 3) {
      model->vertices.emplace_back(floatsToVec3(attribs.vertices[i], attribs.vertices[i + 1], attribs.vertices[i + 2]));
    }

    //for (int i = 0; i < attribs.normals.size(); i += 3) {
    //  model->normals.emplace_back(floatsToVec3(attribs.normals[i], attribs.normals[i + 1], attribs.normals[i + 2]));
    //}

    model->position = glm::vec3(0, 0, 0);

    return model;
  }

  const glm::vec3 &getPosition() const {
    return position;
  }
  void setPosition(const glm::vec3 &position) {
    SimpleGraphicsModel::position = position;
  }

  glm::mat4 getTranslationMatrix() {
    return glm::translate(model, position);
  }
};

#endif //PGR_PROJECT_SIMPLEGRAPHICSMODEL_H
