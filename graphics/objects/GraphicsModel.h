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
#include <RandomGenerator.h>
#include <SDL_surface.h>

namespace PGRgraphics {

/**
 * Base graphics model for rendering. Is build from OBJ file.
 *
 * @author Petr Flajšingr, Igor Frank
 */
class GraphicsModel {
 protected:
  glm::vec3 color;
  std::vector<glm::vec3> vertices;
  std::vector<tinyobj::index_t> indices;
  std::vector<glm::vec3> normals;
  std::vector<glm::vec2> texCoords;

  std::vector<int> vertexIndices;

  SDL_Surface *textureFile = nullptr;

 public:

  static GraphicsModel *LoadFromOBJ(std::string path, glm::vec3 color) {
    auto model = LoadFromFile(path);
    model->color = color;
    return model;

  }

  static GraphicsModel *LoadFromOBJ(std::string path) {
    auto model = LoadFromFile(path);
    model->color = glm::vec3(RandomGenerator::getInstance().getRandomNumber(),
                             RandomGenerator::getInstance().getRandomNumber(),
                             RandomGenerator::getInstance().getRandomNumber());
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

  std::vector<int> &getVertexIndices() {
    return vertexIndices;
  }

  void setVertexIndices(const std::vector<int> &vertexIndices) {
    GraphicsModel::vertexIndices = vertexIndices;
  }

  const glm::vec3 &getColor() const {
    return color;
  }

  void setColor(const glm::vec3 &color) {
    GraphicsModel::color = color;
  }

  const std::vector<int> &getTextureIndices() const {
    return vertexIndices;
  }

  void loadBMPTextureFile(std::string path) {
    textureFile = SDL_LoadBMP(path.c_str());
  }

  SDL_Surface *getTextureFile() {
    return textureFile;
  }

 private:
  static GraphicsModel *LoadFromFile(std::string path) {
    std::string msg = "Loading object from: " + path;
    StdoutLogger::getInstance().logTime(msg);
    auto model = new GraphicsModel();

    tinyobj::attrib_t attribs;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    if (!tinyobj::LoadObj(&attribs, &shapes, &materials, nullptr, nullptr, path.c_str())) {
      std::cerr << "Loading object failed" << std::endl;
      return nullptr;
    }

    model->indices = shapes[0].mesh.indices;

    for (auto indice : model->indices) {
      model->vertexIndices.emplace_back(indice.vertex_index);
      model->normals.emplace_back(attribs.normals[indice.normal_index]);
      if (indice.texcoord_index != -1) {
        model->texCoords[indice.vertex_index] =
            glm::vec2(attribs.texcoords[indice.texcoord_index * 2], attribs.texcoords[indice.texcoord_index * 2 + 1]);
      }
    }

    for (int i = 0; i < attribs.vertices.size(); i += 3) {
      model->vertices.emplace_back(
          glm::vec3(attribs.vertices[i], attribs.vertices[i + 1], attribs.vertices[i + 2]));
    }
    return model;
  }

};

}

#endif //PGR_PROJECT_GRAPHICSMODEL_H
