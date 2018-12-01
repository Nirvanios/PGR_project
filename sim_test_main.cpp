//
// Created by Petr Flajsingr on 2018-11-30.
//

#include <string>
#include <iostream>
#include <fstream>
#include "simulation/Simulation.h"
#include "simulation/forces/GravityForce.h"
#include "simulation/forces/DragForce.h"
#include "simulation/objects/SimulatedModel.h"

int main(int argc, char** argv) {
  Simulation simulation;


  float sphereMass = 1.0f;
  auto movingSphereSimObj = new SimulatedModel(sphereMass,
                                               Active, nullptr);
  simulation.addObject(movingSphereSimObj);

  auto movingSphereSimObj2 = new SimulatedModel(sphereMass,
                                               Active, nullptr);
  simulation.addObject(movingSphereSimObj2);

  auto stationaryCubeSimObj = new SimulatedModel(1000.0f,
                                      Passive, nullptr);
  simulation.addObject(stationaryCubeSimObj);

  float stiffness = 8.0f;
  float damping = 0.1f;
  simulation.addSpring(stiffness, damping, stationaryCubeSimObj,
                      movingSphereSimObj);

  simulation.addSpring(stiffness, damping, movingSphereSimObj2,
                       movingSphereSimObj);

  auto gravity = new GravityForce();
  simulation.addGlobalForce(gravity);

  float dragCoefficient = 0.5f;
  auto air = new DragForce();
  air->setDragCoefficient(dragCoefficient);
  simulation.addGlobalForce(air);



  std::ofstream ofstream;
  ofstream.open("/Users/petr/Desktop/log.txt");
  std::ofstream ofstream1;
  ofstream1.open("/Users/petr/Desktop/log1.txt");
  std::ofstream ofstream2;
  ofstream2.open("/Users/petr/Desktop/log2.txt");
  size_t time = 0;
  while(true) {
    simulation.update(time);
    stationaryCubeSimObj->setCurrentPosition(stationaryCubeSimObj->getCurrectPosition() + glm::vec3(0.1f, 0, 0));

    if (time > 1000) {
      stationaryCubeSimObj->setCurrentPosition(stationaryCubeSimObj->getCurrectPosition() + glm::vec3(0, 0.1f, 0));
    }
    auto tosave = std::to_string(movingSphereSimObj->getCurrectPosition().x)
        + ";"
        + std::to_string(movingSphereSimObj->getCurrectPosition().y)
        + ";"
        + std::to_string(movingSphereSimObj->getCurrectPosition().z)
        + "\n";

    auto toSave2 = std::to_string(stationaryCubeSimObj->getCurrectPosition().x)
        + ";"
        + std::to_string(stationaryCubeSimObj->getCurrectPosition().y)
        + ";"
        + std::to_string(stationaryCubeSimObj->getCurrectPosition().z)
        + "\n";

    auto toSave3 = std::to_string(movingSphereSimObj2->getCurrectPosition().x)
        + ";"
        + std::to_string(movingSphereSimObj2->getCurrectPosition().y)
        + ";"
        + std::to_string(movingSphereSimObj2->getCurrectPosition().z)
        + "\n";

    ofstream.write(tosave.c_str(), tosave.size());
    ofstream1.write(toSave2.c_str(), toSave2.size());
    ofstream2.write(toSave3.c_str(), toSave3.size());

    time += 1;
    if (time == 10000) {
      break;
    }
  }

  ofstream.close();
  ofstream1.close();
  ofstream2.close();



}