//
// Created by Petr Flajsingr on 2018-12-04.
//

#ifndef PGR_PROJECT_GRAPHICSMODEL_H
#define PGR_PROJECT_GRAPHICSMODEL_H

#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <OBJ_Loader.h>

/**
 * Base graphics model for rendering. Is build from OBJ file.
 */
class GraphicsModel {
 protected:
  std::vector<glm::vec3> vertices;
  std::vector<unsigned int> indices;
  std::vector<glm::vec3> normals;
  std::vector<glm::vec2> texCoords;

  static glm::vec3 vector3toGLMvec3(objl::Vector3 &vector3) {
    return glm::vec3(vector3.X, vector3.Y, vector3.Z);
  }

  static glm::vec2 vector2toGLMvec2(objl::Vector2 &vector2) {
    return glm::vec2(vector2.X, vector2.Y);
  }
 public:
  static GraphicsModel* LoadFromOBJ(std::string path) {
    auto model = new GraphicsModel();
    objl::Loader loader;

    loader.LoadFile(path);

    model->indices = loader.LoadedIndices;

    for (auto vertex : loader.LoadedVertices) {
      model->vertices.emplace_back(vector3toGLMvec3(vertex.Position));
      model->normals.emplace_back(vector3toGLMvec3(vertex.Normal));
      model->texCoords.emplace_back(vector2toGLMvec2(vertex.TextureCoordinate));
    }

    return model;
  }

  const std::vector<glm::vec3> &getVertices() const {
    return vertices;
  }

  void setVertices(const std::vector<glm::vec3> &vertices) {
    GraphicsModel::vertices = vertices;
  }

  const std::vector<unsigned int> &getIndices() const {
    return indices;
  }

  void setIndices(const std::vector<unsigned int> &indices) {
    GraphicsModel::indices = indices;
  }

  const std::vector<glm::vec3> &getNormals() const {
    return normals;
  }

  void setNormals(const std::vector<glm::vec3> &normals) {
    GraphicsModel::normals = normals;
  }

  const std::vector<glm::vec2> &getTexCoords() const {
    return texCoords;
  }

  void setTexCoords(const std::vector<glm::vec2> &texCoords) {
    GraphicsModel::texCoords = texCoords;
  }
};

#endif //PGR_PROJECT_GRAPHICSMODEL_H
