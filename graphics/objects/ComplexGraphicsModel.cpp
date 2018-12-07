//
// Created by Petr Flajsingr on 2018-12-04.
//

#include "ComplexGraphicsModel.h"

void PGRgraphics::ComplexGraphicsModel::setVertex(int index, glm::vec3 value) {
  vertices[index] = value;
}

void PGRgraphics::ComplexGraphicsModel::computeNormals() {
  std::for_each(normals.begin(), normals.end(),
                [](glm::vec3 &value) {
                  value = glm::vec3(0.0f);
                });

  for (int i = 0; i < indices.size(); i += 3) {
    glm::vec3 tmpVec =
        glm::normalize(glm::cross(vertices[indices[i + 1].vertex_index] - vertices[indices[i].vertex_index],
                                  vertices[indices[i + 2].vertex_index] - vertices[indices[i].vertex_index]));
    normals[indices[i].vertex_index] += tmpVec;
    normals[indices[i + 1].vertex_index] += tmpVec;
    normals[indices[i + 2].vertex_index] += tmpVec;
  }

  std::for_each(normals.begin(), normals.end(),
                [](glm::vec3 &value) {
                  value = glm::normalize(value);
                });

}

PGRgraphics::ComplexGraphicsModel *PGRgraphics::ComplexGraphicsModel::LoadFromOBJ(std::string path) {
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
PGRgraphics::ComplexGraphicsModel *PGRgraphics::ComplexGraphicsModel::clone() {
  auto result = new PGRgraphics::ComplexGraphicsModel();
  result->setVertexIndices(getVertexIndices());
  result->setIndices(getIndices());
  result->setNormals(getNormals());
  result->setTexCoords(getTexCoords());
  result->setVertices(getVertices());
  return result;
}
