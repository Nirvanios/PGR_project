//
// Created by Petr Flajsingr on 2018-12-04.
//

#ifndef PGR_PROJECT_SIMPLEGRAPHICSMODEL_H
#define PGR_PROJECT_SIMPLEGRAPHICSMODEL_H

#include <glm/gtc/matrix_transform.hpp>
#include "GraphicsModel.h"

class SimpleGraphicsModel : public GraphicsModel {
 private:
  const glm::mat4 model = glm::mat4(1.f);
 protected:
  glm::vec3 position;
 public:
  static SimpleGraphicsModel* LoadFromOBJ(std::string path) {
    auto model = new SimpleGraphicsModel();
    objl::Loader loader;

    loader.LoadFile(path);

    model->indices = loader.LoadedIndices;

    for (auto vertex : loader.LoadedVertices) {
      model->vertices.emplace_back(vector3toGLMvec3(vertex.Position));
      model->normals.emplace_back(vector3toGLMvec3(vertex.Normal));
      model->texCoords.emplace_back(vector2toGLMvec2(vertex.TextureCoordinate));
    }

    model->position = glm::vec3(0, 0, 0);

    return model;
  }

  glm::mat4 getTranslationMatrix() {
    return glm::translate(model, position);
  }
};

#endif //PGR_PROJECT_SIMPLEGRAPHICSMODEL_H
