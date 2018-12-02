//
// Created by Petr Flajsingr on 2018-12-01.
//

#include <iostream>
#include <LengthConstraint.h>
#include "ClothSimulation.h"
ClothSimulation::ClothSimulation(float mass,
                                 float structStiffness,
                                 float structDamping,
                                 float shearStiffness,
                                 float shearDamping,
                                 float bendStiffness,
                                 float bendDamping) {
  createVertices(mass);

  connectSprings(structStiffness, structDamping,
      shearStiffness, shearDamping,
      bendStiffness, bendDamping);
}
void ClothSimulation::createVertices(float mass) {
  int vertexCount = 10;
  float vertexMass = mass / vertexCount;

  vertices.emplace_back(new SimVertex(vertexMass, Active, 0, glm::vec3(0, 0.f, 0)));
  vertices.emplace_back(new SimVertex(vertexMass, Active, 1, glm::vec3(0.1f, 0.f, 0)));
  vertices.emplace_back(new SimVertex(vertexMass, Active, 2, glm::vec3(0.2f, 0.f, 0)));
  vertices.emplace_back(new SimVertex(vertexMass, Active, 3, glm::vec3(0.3f, 0.f, 0)));
  vertices.emplace_back(new SimVertex(vertexMass, Active, 4, glm::vec3(0.4f, 0.f, 0)));


  vertices.emplace_back(new SimVertex(vertexMass, Active, 5, glm::vec3(0, 0.1f, 0)));
  vertices.emplace_back(new SimVertex(vertexMass, Active, 6, glm::vec3(0.1f, 0.1f, 0)));
  vertices.emplace_back(new SimVertex(vertexMass, Active, 7, glm::vec3(0.2f, 0.1f, 0)));
  vertices.emplace_back(new SimVertex(vertexMass, Active, 8, glm::vec3(0.3f, 0.1f, 0)));
  vertices.emplace_back(new SimVertex(vertexMass, Active, 9, glm::vec3(0.4f, 0.1f, 0)));

  for (auto vertex : vertices) {
    addObject(vertex);
    std::cout << vertex->getCurrectPosition().x << ";"
        << vertex->getCurrectPosition().y << ";"
        << vertex->getCurrectPosition().z << "" << std::endl;
  }


}
void ClothSimulation::connectSprings(float structStiffness,
                                     float structDamping,
                                     float shearStiffness,
                                     float shearDamping,
                                     float bendStiffness,
                                     float bendDamping) {

}
void ClothSimulation::update(SimTime time) {
  Simulation::update(time);


}
