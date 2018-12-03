//
// Created by Petr Flajsingr on 2018-11-30.
//

#include <string>
#include <iostream>
#include <fstream>
#include "graphicObjects/SimpleGraphicsModel.h"
#include "Simulation.h"
#include "GravityForce.h"
#include "DragForce.h"
#include "SimObject.h"
#include "ClothSimulation.h"
#include "PointConstraint.h"
#include "ConstantForce.h"

#define SPRING
#define NLOG

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
  std::ofstream ofstream3;
  ofstream3.open("/Users/petr/Desktop/log3.txt");
  size_t time = 0;
  while(true) {
    simulation.update(time);

    auto tosave = std::to_string(simulation.getVertices()[0]->getCurrectPosition().x)
        + ";"
        + std::to_string(simulation.getVertices()[0]->getCurrectPosition().y)
        + ";"
        + std::to_string(simulation.getVertices()[0]->getCurrectPosition().z)
        + "\n";
    ofstream.write(tosave.c_str(), tosave.size());

    tosave = std::to_string(simulation.getVertices()[4]->getCurrectPosition().x)
        + ";"
        + std::to_string(simulation.getVertices()[4]->getCurrectPosition().y)
        + ";"
        + std::to_string(simulation.getVertices()[4]->getCurrectPosition().z)
        + "\n";
    ofstream1.write(tosave.c_str(), tosave.size());

    tosave = std::to_string(simulation.getVertices()[2]->getCurrectPosition().x)
        + ";"
        + std::to_string(simulation.getVertices()[2]->getCurrectPosition().y)
        + ";"
        + std::to_string(simulation.getVertices()[2]->getCurrectPosition().z)
        + "\n";
    ofstream2.write(tosave.c_str(), tosave.size());

    tosave = std::to_string(simulation.getVertices()[6]->getCurrectPosition().x)
        + ";"
        + std::to_string(simulation.getVertices()[6]->getCurrectPosition().y)
        + ";"
        + std::to_string(simulation.getVertices()[6]->getCurrectPosition().z)
        + "\n";
    ofstream3.write(tosave.c_str(), tosave.size());
    time += 1;
    if (time == 1000) {
      break;
    }
  }

  ofstream.close();
  ofstream1.close();
  ofstream2.close();
  ofstream3.close();

#endif

#ifdef SPRING
  PGRsim::Simulation simulation;

  auto sphereMass = 1.0f;
  auto sphereAPos = glm::vec3(0, 0, 0);
  auto movingSphereSimObj = new PGRsim::SimpleObject(sphereMass,
                                                 PGRsim::Active, );
  simulation.addObject(movingSphereSimObj);

  auto sphereBPos = glm::vec3(0.2f, 0, 0);
  auto movingSphereSimObj2 = new PGRsim::SimpleObject(sphereMass,
                                                  PGRsim::Active, );
  simulation.addObject(movingSphereSimObj2);

  auto cubePos = glm::vec3(0.1f, 0.3f, 0.3f);
  auto stationaryCubeSimObj = new PGRsim::SimpleObject(1000.0f,
                                                   PGRsim::Passive, );
  simulation.addObject(stationaryCubeSimObj);

  auto sphereCPos = glm::vec3(10.0f, 0, 0);
  auto movingSphereSimObj3 = new PGRsim::SimpleObject(sphereMass,
                                                  PGRsim::Active, );
  simulation.addObject(movingSphereSimObj3);

  float stiffness = 8.0f;
  float damping = 0.1f;
  simulation.addSpring(stiffness, damping, stationaryCubeSimObj,
                      movingSphereSimObj);

  simulation.addSpring(stiffness, damping, movingSphereSimObj2,
                       movingSphereSimObj);

  simulation.addSpring(stiffness, damping, movingSphereSimObj3,
                       stationaryCubeSimObj);

  auto gravity = new PGRsim::GravityForce();
  simulation.addGlobalForce(gravity);

  float dragCoefficient = 0.5f;
  auto air = new PGRsim::DragForce();
  air->setDragCoefficient(dragCoefficient);
  simulation.addGlobalForce(air);


#ifdef LOG
  std::ofstream ofstream;
  ofstream.open("/Users/petr/Desktop/log.txt");
  std::ofstream ofstream1;
  ofstream1.open("/Users/petr/Desktop/log1.txt");
  std::ofstream ofstream2;
  ofstream2.open("/Users/petr/Desktop/log2.txt");
  std::ofstream ofstream3;
  ofstream3.open("/Users/petr/Desktop/log3.txt");
#endif

  simulation.setConstraintIterations(0);

  size_t time = 0;
  while(true) {
    simulation.update(time);
    stationaryCubeSimObj->setCurrentPosition(stationaryCubeSimObj->getCurrectPosition() + glm::vec3(0.01f, 0, 0));


    // z movingSphereSimObj movingSphereSimObj2 movingSphereSimObj3 stačí vytáhnout getCurrentPosition a na to vykreslit třeba krychličku
    // z stationaryCubeSimObj taky
    // ty krychličky nějak rozumně velký, 0.1f třeba?

    // lajny mezi:
    //  - stationaryCubeSimObj - movingSphereSimObj
    //  - stationaryCubeSimObj - movingSphereSimObj3
    //  - movingSphereSimObj2  - movingSphereSimObj
    // presneji mezi jejich getCurrentPosition()


    // každé opakování tohoto cyklu je 1/60 sekundy simulace



#ifdef LOG
    auto tosave = std::to_string(movingSphereSimObj->getCurrectPosition().x)
        + ";"
        + std::to_string(movingSphereSimObj->getCurrectPosition().y)
        + ";"
        + std::to_string(movingSphereSimObj->getCurrectPosition().z)
        + "\n";
    ofstream.write(tosave.c_str(), tosave.size());

    tosave = std::to_string(stationaryCubeSimObj->getCurrectPosition().x)
        + ";"
        + std::to_string(stationaryCubeSimObj->getCurrectPosition().y)
        + ";"
        + std::to_string(stationaryCubeSimObj->getCurrectPosition().z)
        + "\n";
    ofstream1.write(tosave.c_str(), tosave.size());

    tosave = std::to_string(movingSphereSimObj2->getCurrectPosition().x)
        + ";"
        + std::to_string(movingSphereSimObj2->getCurrectPosition().y)
        + ";"
        + std::to_string(movingSphereSimObj2->getCurrectPosition().z)
        + "\n";
    ofstream2.write(tosave.c_str(), tosave.size());

    tosave = std::to_string(movingSphereSimObj3->getCurrectPosition().x)
        + ";"
        + std::to_string(movingSphereSimObj3->getCurrectPosition().y)
        + ";"
        + std::to_string(movingSphereSimObj3->getCurrectPosition().z)
        + "\n";
    ofstream3.write(tosave.c_str(), tosave.size());

#endif

    time += 1;
    if (time == 3000) {
      break;
    }
  }

#ifdef LOG
  ofstream.close();
  ofstream1.close();
  ofstream2.close();
  ofstream3.close();
#endif



#endif


}