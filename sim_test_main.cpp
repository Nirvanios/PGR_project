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
#include "simulation/ClothSimulation.h"
#include "simulation/objects/PointConstraint.h"

#define SPRING

int main(int argc, char** argv) {

#ifdef CLOTH

  ClothSimulation simulation(2.0f, 2.0f, 0.02f, 2.0f, 0.02f, 2.0f, 0.02f);

  simulation.setConstraintIterations(10);

  auto gravity = new GravityForce();
  simulation.addGlobalForce(gravity);

  auto leftConstraint = new PointConstraint(simulation.getVertices()[0]->getCurrectPosition(),
                                            simulation.getVertices()[0]);

  auto rightConstraint = new PointConstraint(simulation.getVertices()[4]->getCurrectPosition(),
                                            simulation.getVertices()[4]);

  simulation.addConstraint(leftConstraint);
  simulation.addConstraint(rightConstraint);

  simulation.setIntegrator(new VerletIntegrator(1.0f / 60.0f));


  std::ofstream ofstream;
  ofstream.open("/Users/petr/Desktop/log.txt");
  std::ofstream ofstream1;
  ofstream1.open("/Users/petr/Desktop/log1.txt");
  std::ofstream ofstream2;
  ofstream2.open("/Users/petr/Desktop/log2.txt");
  size_t time = 0;
  while(true) {
    simulation.update(time);

    auto tosave = std::to_string(simulation.getVertices()[0]->getCurrectPosition().x)
        + ";"
        + std::to_string(simulation.getVertices()[0]->getCurrectPosition().y)
        + ";"
        + std::to_string(simulation.getVertices()[0]->getCurrectPosition().z)
        + "\n";

    auto toSave2 = std::to_string(simulation.getVertices()[4]->getCurrectPosition().x)
        + ";"
        + std::to_string(simulation.getVertices()[4]->getCurrectPosition().y)
        + ";"
        + std::to_string(simulation.getVertices()[4]->getCurrectPosition().z)
        + "\n";

    auto toSave3 = std::to_string(simulation.getVertices()[2]->getCurrectPosition().x)
        + ";"
        + std::to_string(simulation.getVertices()[2]->getCurrectPosition().y)
        + ";"
        + std::to_string(simulation.getVertices()[2]->getCurrectPosition().z)
        + "\n";

    ofstream.write(tosave.c_str(), tosave.size());
    ofstream1.write(toSave2.c_str(), toSave2.size());
    ofstream2.write(toSave3.c_str(), toSave3.size());

    time += 1;
    if (time == 1000) {
      break;
    }
  }

  ofstream.close();
  ofstream1.close();
  ofstream2.close();

#endif

#ifdef SPRING
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

  //simulation.addSpring(stiffness, damping, movingSphereSimObj2,
  //                     movingSphereSimObj);

  auto gravity = new GravityForce();
  simulation.addGlobalForce(gravity);

  float dragCoefficient = 0.5f;
  auto air = new DragForce();
  air->setDragCoefficient(dragCoefficient);
  simulation.addGlobalForce(air);

  size_t time = 0;
  while(true) {
    simulation.update(time);

    // z movingSphereSimObj2 a movingSphereSimObj stačí vytáhnout getCurrentPosition a na to vykreslit třeba krychličku
    // z stationaryCubeSimObj taky
    // mezi tyto ziskane objekty muzes vykreslit lajnu
    // každé opakování tohoto cyklu je 1/60 sekundy simulace

    time += 1;
    if (time == 100000) {
      break;
    }
  }

#endif


}