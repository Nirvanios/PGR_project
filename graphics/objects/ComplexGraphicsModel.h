//
// Created by Petr Flajsingr on 2018-12-04.
//

#ifndef PGR_PROJECT_COMPLEXGRAPHICSMODEL_H
#define PGR_PROJECT_COMPLEXGRAPHICSMODEL_H

#include <StdoutLogger.h>
#include "GraphicsModel.h"

namespace PGRgraphics {

class ComplexGraphicsModel : public GraphicsModel {
 private:
 protected:
 public:

  static ComplexGraphicsModel *LoadFromOBJ(std::string path) {
    std::string msg = "Loading object from: " + path;
    StdoutLogger::getInstance().logTime(msg);
    auto model = new ComplexGraphicsModel();

    tinyobj::attrib_t attribs;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string error;
    if (!tinyobj::LoadObj(&attribs, &shapes, &materials, nullptr, &error, path.c_str())) {
      std::cerr << "Loading object failed: " + error << std::endl;
      return nullptr;
    }

    model->indices = shapes[0].mesh.indices;

    model->normals.resize(attribs.vertices.size());

    std::for_each(model->normals.begin(), model->normals.end(),
                  [](glm::vec3 &value) {
                    value = glm::vec3(0.0f);
                  });

    for (auto indice : model->indices) {
      model->vertexIndices.emplace_back(indice.vertex_index);
      model->normals[indice.vertex_index] += glm::vec3(attribs.normals[indice.normal_index * 3],
                                                       attribs.normals[indice.normal_index * 3 + 1],
                                                       attribs.normals[indice.normal_index * 3 + 2]);
    }

    std::for_each(model->normals.begin(), model->normals.end(),
                  [](glm::vec3 &value) {
                    value = glm::normalize(value);
                  });

    for (int i = 0; i < attribs.vertices.size(); i += 3) {
      model->vertices.emplace_back(floatsToVec3(attribs.vertices[i], attribs.vertices[i + 1], attribs.vertices[i + 2]));
    }

    return model;
  }

  void setVertex(int index, glm::vec3 value);
};
}

#endif //PGR_PROJECT_COMPLEXGRAPHICSMODEL_H
