//
// Created by Petr Flajsingr on 2018-12-01.
//

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

  vertices.emplace_back(new SimulatedVertex(vertexMass, Active, 0, glm::vec3(0, 0.f, 0)));
  vertices.emplace_back(new SimulatedVertex(vertexMass, Active, 1, glm::vec3(0.1f, 0.f, 0)));
  vertices.emplace_back(new SimulatedVertex(vertexMass, Active, 2, glm::vec3(0.2f, 0.f, 0)));
  vertices.emplace_back(new SimulatedVertex(vertexMass, Active, 3, glm::vec3(0.3f, 0.f, 0)));
  vertices.emplace_back(new SimulatedVertex(vertexMass, Active, 4, glm::vec3(0.4f, 0.f, 0)));


  vertices.emplace_back(new SimulatedVertex(vertexMass, Active, 5, glm::vec3(0, 0.1f, 0)));
  vertices.emplace_back(new SimulatedVertex(vertexMass, Active, 6, glm::vec3(0.1f, 0.1f, 0)));
  vertices.emplace_back(new SimulatedVertex(vertexMass, Active, 7, glm::vec3(0.2f, 0.1f, 0)));
  vertices.emplace_back(new SimulatedVertex(vertexMass, Active, 8, glm::vec3(0.3f, 0.1f, 0)));
  vertices.emplace_back(new SimulatedVertex(vertexMass, Active, 9, glm::vec3(0.4f, 0.1f, 0)));

  for (auto vertex : vertices) {
    addObject(vertex);
  }


}
void ClothSimulation::connectSprings(float structStiffness,
                                     float structDamping,
                                     float shearStiffness,
                                     float shearDamping,
                                     float bendStiffness,
                                     float bendDamping) {
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 2; y++) {
      int idA = x + y * 4;
      int idB = x + 1 + y * 4;

      addSpring(structStiffness, structDamping, vertices[idA], vertices[idB]);
    }
  }

  for (int x = 0; x < 5; x++) {
    for (int y = 0; y < 1; y++) {
      int idA = x + y * 4;
      int idB = x + (y + 1) * 4;

      addSpring(structStiffness, structDamping, vertices[idA], vertices[idB]);
    }
  }
}
void ClothSimulation::update(SimulationTime time) {
  Simulation::update(time);


}
