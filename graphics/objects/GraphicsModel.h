//
// Created by Petr Flajsingr on 2018-12-04.
//

#ifndef PGR_PROJECT_GRAPHICSMODEL_H
#define PGR_PROJECT_GRAPHICSMODEL_H

#include <glm/glm.hpp>
#include <vector>
#include <string>
#include "../../third_party/tiny_obj_loader.h"
#include <iostream>

namespace PGRgraphics {

/**
 * Base graphics model for rendering. Is build from OBJ file.
 */
class GraphicsModel {
 protected:
  std::vector<glm::vec3> vertices;
  std::vector<tinyobj::index_t> indices;
  std::vector<glm::vec3> normals;
  std::vector<glm::vec2> texCoords;

  std::vector<int> vertexIndices;

  static glm::vec3 floatsToVec3(float x, float y, float z) {
    return glm::vec3(x, y, z);
  }

  static glm::vec2 floatsToVec2(float x, float y) {
    return glm::vec2(x, y);
  }
 public:
  static GraphicsModel* LoadFromOBJ(std::string path) {
    std::cout << "Loading object from: " << path << std::endl;
    auto model = new GraphicsModel();

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
      model->normals.emplace_back(attribs.normals[indice.normal_index]);
    }

    for (int i = 0; i < attribs.vertices.size(); i += 3) {
      model->vertices.emplace_back(floatsToVec3(attribs.vertices[i], attribs.vertices[i + 1], attribs.vertices[i + 2]));
    }

    /*for (int i = 0; i < attribs.normals.size(); i += 3) {
      model->normals.emplace_back(floatsToVec3(attribs.normals[i], attribs.normals[i + 1], attribs.normals[i + 2]));
    }*/


    return model;
  }

  virtual ~GraphicsModel() = default;

  const std::vector<glm::vec3> &getVertices() const {
    return vertices;
  }

  void setVertices(const std::vector<glm::vec3> &vertices) {
    GraphicsModel::vertices = vertices;
  }

  const std::vector<tinyobj::index_t> &getIndices() const {
    return indices;
  }

  void setIndices(const std::vector<tinyobj::index_t> &indices) {
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

  const std::vector<int> &getVertexIndices() const {
    return vertexIndices;
  }
};
}

#endif //PGR_PROJECT_GRAPHICSMODEL_H
