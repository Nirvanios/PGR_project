//
// Created by Petr Flajsingr on 2018-12-07.
//

#ifndef PGR_PROJECT_GEOUTILS_H
#define PGR_PROJECT_GEOUTILS_H

#include <glm/glm.hpp>

namespace PGRutils {

glm::vec3 baryToCartesian(glm::vec3 &baryCoords, glm::vec3 &vertexA, glm::vec3 &vertexB, glm::vec3 &vertexC) {
  return baryCoords.x * vertexA + baryCoords.y * vertexB + baryCoords.z * vertexC;
}

glm::vec3 baryToCartesian(glm::vec2 &baryCoords, glm::vec3 &vertexA, glm::vec3 &vertexB, glm::vec3 &vertexC) {
  return (1 - baryCoords.x - baryCoords.y) * vertexA + baryCoords.x * vertexB + baryCoords.y * vertexC;
}

glm::vec3 pointOnLine(glm::vec3 &A, glm::vec3 &B, float AP) {
  auto D = B - A;
  return A + D / glm::normalize(D) * AP;
}

}

#endif //PGR_PROJECT_GEOUTILS_H
