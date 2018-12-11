//
// Created by Petr Flajsingr on 2018-12-07.
//

#ifndef PGR_PROJECT_GEOUTILS_H
#define PGR_PROJECT_GEOUTILS_H

#include <glm/glm.hpp>

namespace PGRutils {

/**
 * Convert barymetric coordinates to cartesian
 * @param baryCoords barycentric coordinates on triangle
 * @param vertexA first triangle vertex
 * @param vertexB second triangle vertex
 * @param vertexC third triangle vertex
 * @return cartesian coordinates on a triangle
 */
glm::vec3 baryToCartesian(glm::vec3 &baryCoords, glm::vec3 &vertexA, glm::vec3 &vertexB, glm::vec3 &vertexC) {
  return baryCoords.x * vertexA + baryCoords.y * vertexB + baryCoords.z * vertexC;
}

/**
 * Convert barymetric coordinates to cartesian
 * @param baryCoords barycentric coordinates on triangle
 * @param vertexA first triangle vertex
 * @param vertexB second triangle vertex
 * @param vertexC third triangle vertex
 * @return cartesian coordinates on a triangle
 */
glm::vec3 baryToCartesian(glm::vec2 &baryCoords, glm::vec3 &vertexA, glm::vec3 &vertexB, glm::vec3 &vertexC) {
  return (1 - baryCoords.x - baryCoords.y) * vertexA + baryCoords.x * vertexB + baryCoords.y * vertexC;
}
}

#endif //PGR_PROJECT_GEOUTILS_H
