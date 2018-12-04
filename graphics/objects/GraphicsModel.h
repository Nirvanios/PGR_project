//
// Created by Petr Flajsingr on 2018-12-04.
//

#ifndef PGR_PROJECT_GRAPHICSMODEL_H
#define PGR_PROJECT_GRAPHICSMODEL_H

#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <OBJ_Loader.h>

class GraphicsModel {
 private:
 protected:
  std::vector<glm::vec3> vertices;
  std::vector<unsigned int> indices;
  std::vector<glm::vec3> normals;
  std::vector<glm::vec3> texCoords;
 public:
  GraphicsModel* LoadFromOBJ(std::string path) {
    auto model = new GraphicsModel();
    objl::Loader loader;

    loader.LoadFile(path);

    indices = loader.LoadedIndices;

    for (auto vertex : loader.LoadedVertices) {
      vertices.emplace_back(vertex.Position);
      normals.emplace_back(vertex.Normal);
      texCoords.emplace_back(vertex.TextureCoordinate);
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

  const std::vector<glm::vec3> &getTexCoords() const {
    return texCoords;
  }

  void setTexCoords(const std::vector<glm::vec3> &texCoords) {
    GraphicsModel::texCoords = texCoords;
  }
};

#endif //PGR_PROJECT_GRAPHICSMODEL_H
