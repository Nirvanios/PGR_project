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
  auto stationaryCubeSimObj = new SimulatedModel(1000.0f,
                                      Passive, nullptr);
  simulation.addObject(stationaryCubeSimObj);

  float stiffness = 8.0f;
  float damping = 0.1f;
  simulation.addSpring(stiffness, damping, stationaryCubeSimObj,
                      movingSphereSimObj);

  auto gravity = new GravityForce();
  simulation.addGlobalForce(gravity);

  float dragCoefficient = 0.5f;
  auto air = new DragForce();
  air->setDragCoefficient(dragCoefficient);
  simulation.addGlobalForce(air);



  std::ofstream ofstream;
  ofstream.open("/Users/petr/Desktop/log.txt");
  size_t time = 0;
  while(true) {
    simulation.update(time);
    auto tosave = std::to_string(movingSphereSimObj->getCurrectPosition().x)
        + ";"
        + std::to_string(movingSphereSimObj->getCurrectPosition().y)
        + ";"
        + std::to_string(movingSphereSimObj->getCurrectPosition().z)
        + "\n";

    ofstream.write(tosave.c_str(), tosave.size());

    time += 1;
    if (time == 100000) {
      break;
    }
  }

  ofstream.close();



}