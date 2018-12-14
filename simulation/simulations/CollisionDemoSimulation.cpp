//
// Created by Petr Flajsingr on 2018-12-06.
//

#include <ComplexObject.h>
#include <thread>
#include "CollisionDemoSimulation.h"

int width = 17, height = 17;

void PGRsim::CollisionDemoSimulation::prepareClothObject(std::string filePath, std::string texPath) {
  auto clothObject = new ComplexObject(10.0f, Active, PGRgraphics::ComplexGraphicsModel::LoadFromOBJ(filePath));
  if(texPath != "") {
      clothObject->getObjectModel()->loadBMPTextureFile(texPath);
  }

  auto vertexIndices = clothObject->getObjectModel()->getVertexIndices();
  auto vertices = clothObject->getSimVertices();

  float s = 8.0f, d = 0.1f;

  int index;
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      index = x * height + y;

      if (y < height - 1) {
        clothObject->addSpring(s, d, index, index + 1);
        clothObject->addConstraint(glm::distance(vertices[index]->getCurrectPosition(),
                                                 vertices[index + 1]->getCurrectPosition()),
                                   index,
                                   index + 1);

        if (x < width - 1) {
          clothObject->addSpring(s, d, index, index + 1);
          clothObject->addConstraint(glm::distance(vertices[index]->getCurrectPosition(),
                                                   vertices[index + width + 1]->getCurrectPosition()),
                                     index,
                                     index + width + 1);

          if (y > 0) {
            clothObject->addSpring(s, d, index, index + width - 1);
            clothObject->addConstraint(glm::distance(vertices[index]->getCurrectPosition(),
                                                     vertices[index + width - 1]->getCurrectPosition()),
                                       index,
                                       index + width - 1);
          }
        }
      }

      if (x < width - 1) {
        clothObject->addSpring(s, d, index, index + width);
        clothObject->addConstraint(glm::distance(vertices[index]->getCurrectPosition(),
                                                 vertices[index + width]->getCurrectPosition()),
                                   index,
                                   index + width);
      }

      if (y < height - 2) {
        clothObject->addSpring(s, d, index, index + 2);
        clothObject->addConstraint(glm::distance(vertices[index]->getCurrectPosition(),
                                                 vertices[index + 2]->getCurrectPosition()),
                                   index,
                                   index + 2);
      }

      if (x < width - 2) {
        clothObject->addSpring(s, d, index, index + 2 * width);
        clothObject->addConstraint(glm::distance(vertices[index]->getCurrectPosition(),
                                                 vertices[index + 2 * width]->getCurrectPosition()),
                                   index,
                                   index + 2 * width);
      }
    }
  }

  clothObject->addConstraint(glm::vec3(-0.034899, 0.999391, 1), 0);
  clothObject->addConstraint(glm::vec3(-0.034899, 0.999391, -1.000000), 272);

  for (auto constr : clothObject->getConstraints()) {
    addConstraint(constr);
  }

  for (auto spring : clothObject->getSprings()) {
    addSpring(spring);
  }

  for (auto simVertex : clothObject->getSimVertices()) {
    addObject(simVertex);
  }

  addObject(clothObject);
}

void PGRsim::CollisionDemoSimulation::update(PGRsim::SimTime time) {
  collisionChecker.checkCollisions();

  collisionChecker.applyChanges();

  for (auto spring : springs) {
    spring->applyForce();
  }

  glm::vec3 acceleration;
  for (auto object : objects) {
    if (object->getSimulatedObjectType() == Active || object->getSimulatedObjectType() == Shape) {
      for (auto forceGenerator : forces) {
        forceGenerator->applyForce(*object);
      }
    }
  }

  for (auto object : objects) {
    if (object->getSimulatedObjectType() == Active || object->getSimulatedObjectType() == Shape) {
      acceleration = object->getResultantForce() / object->getMass();

      integrator->integrate(acceleration, *object);
    }
  }

  std::thread thread(
      &CollisionDemoSimulation::threadConstraints,
      this,
      0,
      constraints.size() / 2);

  threadConstraints(static_cast<int>(constraints.size() / 2), static_cast<int>(constraints.size()));

  thread.join();

  for (auto object : objects) {
    if (object->getSimulatedObjectType() == Active || object->getSimulatedObjectType() == Shape) {
      object->resetForces();
    }
  }

  for (auto object : objects) {
    object->update(time);
  }
}
void PGRsim::CollisionDemoSimulation::addObject(PGRsim::SimObject *object) {
  auto vertex = dynamic_cast<SimVertex *>(object);
  if (vertex != nullptr) {
    collisionChecker.addObject(vertex);
  }

  Simulation::addObject(object);
}
