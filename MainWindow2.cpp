// Headerphile.com OpenGL Tutorial part 2
// A simple example involving VBOs and a VAO to draw a simple square
// Source code is an adaption / simplicication of : https://www.opengl.org/wiki/Tutorial2:_VAOs,_VBOs,_Vertex_and_Fragment_Shaders_(C_/_SDL)

// Compile :
// 	clang++ main.cpp -lGL -lGLEW -lSDL2 -std=c++11 -o Test
// or
// 	g++ main.cpp -lGL -lGLEW -lSDL2 -std=c++11 -o Test
//
#include <iostream>

//#include "shader.h"
#include "graphicObjects/SimpleGraphicsModelCreator.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Simulation.h>
#include <SimModel.h>
#include <GravityForce.h>
#include <DragForce.h>
#include "graphics/camera/Camera.h"
#include <SnapableSpring.h>
#include <GraphicsCore.h>


auto gravity = new GravityForce;
auto air = new DragForce();

Simulation *simulation;




void prepareSimulation() {
  simulation = new Simulation();


  auto passive1 = new SimModel(1000.0f,
                               Passive,
                               SimpleGraphicsModelCreator::CreateQuad(
                                   0.5f, 0.5f, 0.5f,
                                   0, 0, 0));
  simulation->addObject(passive1);

  auto active1_onPassive1 = new SimModel(1.0f,
                                         Active,
                                         SimpleGraphicsModelCreator::CreateQuad(
                                             0.3f, 0.3f, 0.3f,
                                             1.0f, 0, 0));
  simulation->addObject(active1_onPassive1);

  auto active2_onActive1 = new SimModel(1.0f,
                                          Active,
                                          SimpleGraphicsModelCreator::CreateQuad(
                                              0.3f, 0.3f, 0.3f,
                                              0.3f, 0, 0));
  simulation->addObject(active2_onActive1);

  auto active3_onPassive1 = new SimModel(0.5f,
                                          Active,
                                          SimpleGraphicsModelCreator::CreateQuad(
                                              0.2f, 0.2f, 0.2f,
                                              3.0f, 0, 0));
  simulation->addObject(active3_onPassive1);

  auto active4_onPassive2Passive3 = new SimModel(0.5f,
                                         Active,
                                         SimpleGraphicsModelCreator::CreateQuad(
                                             0.2f, 0.2f, 0.2f,
                                             2.0f, 0, 0.5f));
  simulation->addObject(active4_onPassive2Passive3);

  auto passive2 = new SimModel(1000.0f,
                               Passive,
                               SimpleGraphicsModelCreator::CreateQuad(
                                   0.1f, 0.1f, 0.05f,
                                   1.8f, 0, 1.0f));
  simulation->addObject(passive2);

  auto passive3 = new SimModel(1000.0f,
                               Passive,
                               SimpleGraphicsModelCreator::CreateQuad(
                                   0.1f, 0.1f, 0.05f,
                                   2.0f, 0, 0));
  simulation->addObject(passive3);

  float stiffness = 8.0f;
  float damping = 0.1f;
  simulation->addSpring(stiffness, damping, passive1,
                        active1_onPassive1);

  simulation->addSpring(stiffness, damping, active2_onActive1,
                        active1_onPassive1);

  simulation->addSpring(stiffness, damping, active3_onPassive1,
                        passive1);

  simulation->addSpring(6.0f, 0.2f, active4_onPassive2Passive3,
                        passive2);

  simulation->addSpring(new SnapableSpring(stiffness, damping, active4_onPassive2Passive3,
                                   passive3, 7.0f));
  //simulation->addSpring(4.5f, 0.3f, active4_onPassive2Passive3,
  //                      passive3);

  simulation->addGlobalForce(gravity);

  air->setDragCoefficient(0.5f);
  simulation->addGlobalForce(air);

  simulation->setConstraintIterations(0);
}

void updateSimulation() {
  static SimTime simTime = 0.0f;
  simTime += 1 / 60.0f;
  simulation->update(simTime);
}

int main(int argc, char *argv[]) {
    GraphicsCore graphicsCore;

  if (!graphicsCore.init())
    return -1;

  std::cout << "Seting up VBO + VAO..." << std::endl;

  auto objects = new std::vector<SimpleGraphicsModel *>();


  prepareSimulation();

  auto simObjects = simulation->getObjects();
  for (auto object : simObjects) {
    objects->emplace_back(dynamic_cast<SimModel *>(object)->getObjectModel());
  }

  auto line1 =
      SimpleGraphicsModelCreator::createLine(simObjects[0]->getCurrectPosition(), simObjects[1]->getCurrectPosition());
  objects->emplace_back(line1);
  auto line2 =
      SimpleGraphicsModelCreator::createLine(simObjects[1]->getCurrectPosition(), simObjects[2]->getCurrectPosition());
  objects->emplace_back(line2);
  auto line3 =
      SimpleGraphicsModelCreator::createLine(simObjects[0]->getCurrectPosition(), simObjects[3]->getCurrectPosition());
  objects->emplace_back(line3);
  auto line4 =
      SimpleGraphicsModelCreator::createLine(simObjects[4]->getCurrectPosition(), simObjects[5]->getCurrectPosition());
  objects->emplace_back(line4);
  auto line5 =
      SimpleGraphicsModelCreator::createLine(simObjects[4]->getCurrectPosition(), simObjects[6]->getCurrectPosition());
  objects->emplace_back(line5);

  if (!graphicsCore.setupBufferObjects(objects))
    return -1;

  std::cout << "Rendering..." << std::endl;

  bool is_running = true;
  bool is_simRunning = false;
  bool enableCameraMovement = false;
  bool gravityEnabled = true;
  SDL_Event event;
  while (is_running) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:is_running = false;
          break;
        case SDL_WINDOWEVENT:
          if (event.window.type == SDL_WINDOWEVENT_RESIZED)
            graphicsCore.handleResize();
          break;
        case SDL_KEYDOWN:
          switch (event.key.keysym.sym) {
            case SDLK_LEFT:
              simObjects[6]->setCurrentPosition(simObjects[6]->getCurrectPosition() + glm::vec3(-0.05f, 0, 0));
              break;
            case SDLK_RIGHT:
              simObjects[6]->setCurrentPosition(simObjects[6]->getCurrectPosition() + glm::vec3(0.05f, 0, 0));
              break;
            case SDLK_UP:
              simObjects[6]->setCurrentPosition(simObjects[6]->getCurrectPosition() + glm::vec3(0, 0.05f, 0));
              break;
            case SDLK_DOWN:
              simObjects[6]->setCurrentPosition(simObjects[6]->getCurrectPosition() + glm::vec3(0, -0.05f, 0));
              break;
            case SDLK_w:
            case SDLK_s:
            case SDLK_a:
            case SDLK_d:
              graphicsCore.handleCameraMove(event.key.keysym.sym);
              break;
            case SDLK_g:
              if (gravityEnabled) {
                gravity->disable();
                gravityEnabled = false;
              } else {
                gravity->enable();
                gravityEnabled = true;
              }
              break;
            case SDLK_o:air->setDragCoefficient(air->getDragCoefficient() - 0.05f);
              break;
            case SDLK_p:if (air->getDragCoefficient() > 0.2f) {
              air->setDragCoefficient(air->getDragCoefficient() + 0.05f);
              }
              break;
            case SDLK_SPACE: is_simRunning = !is_simRunning;
              break;
          }
          break;
        case SDL_MOUSEBUTTONDOWN:
          if (event.button.button == SDL_BUTTON_LEFT) {
            enableCameraMovement = true;
          }
          break;
        case SDL_MOUSEBUTTONUP:
          if (event.button.button == SDL_BUTTON_LEFT) {
            enableCameraMovement = false;
          }
        case SDL_MOUSEMOTION:
          if (enableCameraMovement) {
            graphicsCore.handleMouseMove(event.motion.xrel, event.motion.yrel, false);
          }
          break;
      }
    }

    if (is_simRunning) {
      updateSimulation();
      line1->getVertices()[0] = simObjects[0]->getCurrectPosition().x;
      line1->getVertices()[1] = simObjects[0]->getCurrectPosition().y;
      line1->getVertices()[2] = simObjects[0]->getCurrectPosition().z;
      line1->getVertices()[3] = simObjects[1]->getCurrectPosition().x;
      line1->getVertices()[4] = simObjects[1]->getCurrectPosition().y;
      line1->getVertices()[5] = simObjects[1]->getCurrectPosition().z;

      line2->getVertices()[0] = simObjects[1]->getCurrectPosition().x;
      line2->getVertices()[1] = simObjects[1]->getCurrectPosition().y;
      line2->getVertices()[2] = simObjects[1]->getCurrectPosition().z;
      line2->getVertices()[3] = simObjects[2]->getCurrectPosition().x;
      line2->getVertices()[4] = simObjects[2]->getCurrectPosition().y;
      line2->getVertices()[5] = simObjects[2]->getCurrectPosition().z;

      line3->getVertices()[0] = simObjects[0]->getCurrectPosition().x;
      line3->getVertices()[1] = simObjects[0]->getCurrectPosition().y;
      line3->getVertices()[2] = simObjects[0]->getCurrectPosition().z;
      line3->getVertices()[3] = simObjects[3]->getCurrectPosition().x;
      line3->getVertices()[4] = simObjects[3]->getCurrectPosition().y;
      line3->getVertices()[5] = simObjects[3]->getCurrectPosition().z;

      line4->getVertices()[0] = simObjects[4]->getCurrectPosition().x;
      line4->getVertices()[1] = simObjects[4]->getCurrectPosition().y;
      line4->getVertices()[2] = simObjects[4]->getCurrectPosition().z;
      line4->getVertices()[3] = simObjects[5]->getCurrectPosition().x;
      line4->getVertices()[4] = simObjects[5]->getCurrectPosition().y;
      line4->getVertices()[5] = simObjects[5]->getCurrectPosition().z;

      line5->getVertices()[0] = simObjects[4]->getCurrectPosition().x;
      line5->getVertices()[1] = simObjects[4]->getCurrectPosition().y;
      line5->getVertices()[2] = simObjects[4]->getCurrectPosition().z;
      line5->getVertices()[3] = simObjects[6]->getCurrectPosition().x;
      line5->getVertices()[4] = simObjects[6]->getCurrectPosition().y;
      line5->getVertices()[5] = simObjects[6]->getCurrectPosition().z;
    }

    graphicsCore.render(objects);
    SDL_Delay(1000/60);
  }

  graphicsCore.cleanup();

  return 0;
}
