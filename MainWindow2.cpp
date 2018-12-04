// Headerphile.com OpenGL Tutorial part 2
// A simple example involving VBOs and a VAO to draw a simple square
// Source code is an adaption / simplicication of : https://www.opengl.org/wiki/Tutorial2:_VAOs,_VBOs,_Vertex_and_Fragment_Shaders_(C_/_SDL)

// Compile :
// 	clang++ main.cpp -lGL -lGLEW -lSDL2 -std=c++11 -o Test
// or
// 	g++ main.cpp -lGL -lGLEW -lSDL2 -std=c++11 -o Test
//
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Simulation.h>
#include <GravityForce.h>
#include <DragForce.h>
#include "graphics/camera/Camera.h"
#include <SnapableSpring.h>
#include <core/GraphicsCore.h>
#include <SimObject.h>
#include <SimpleObject.h>
#include <objects/GraphicsModel.h>
#include <objects/SimpleGraphicsModel.h>

auto gravity = new PGRsim::GravityForce;
auto air = new PGRsim::DragForce();

PGRsim::Simulation *simulation;




void prepareSimulation() {
  simulation = new PGRsim::Simulation();


  auto passive1 = new PGRsim::SimpleObject(1000.0f,
                                       PGRsim::Passive,
                               SimpleGraphicsModel::LoadFromOBJ("test.obj"));
  simulation->addObject(passive1);

  auto model = SimpleGraphicsModel::LoadFromOBJ("test.obj");
  model->setPosition(glm::vec3(0, -2.0f, 0));
  auto active1_onPassive1 = new PGRsim::SimpleObject(1.0f,
                                                 PGRsim::Active,
                                                     model);
  simulation->addObject(active1_onPassive1);


  float stiffness = 8.0f;
  float damping = 0.1f;
  simulation->addSpring(stiffness, damping, passive1,
                        active1_onPassive1);

  simulation->addGlobalForce(gravity);

  air->setDragCoefficient(0.5f);
  simulation->addGlobalForce(air);

  simulation->setConstraintIterations(0);
}

void updateSimulation() {
  static PGRsim::SimTime simTime = 0.0f;
  simTime += 1 / 60.0f;
  simulation->update(simTime);
}

int main(int argc, char *argv[]) {
  GraphicsCore graphicsCore;

  if (!graphicsCore.init())
    return -1;


  std::cout << "Seting up VBO + VAO..." << std::endl;

  /*
  objects.emplace_back(SimpleGraphicsModel::LoadFromOBJ("small_ball.obj"));

  if (!graphicsCore.setupBufferObjects(objects))
    return -1;


  bool is_running = true;
  bool is_simRunning = false;
  bool enableCameraMovement = false;
  bool gravityEnabled = true;
  SDL_Event event;

  while (is_running) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          is_running = false;
              break;
        case SDL_WINDOWEVENT:
          if (event.window.type == SDL_WINDOWEVENT_RESIZED)
            graphicsCore.handleResize();
              break;
        case SDL_KEYDOWN:
          switch (event.key.keysym.sym) {
            case SDLK_w:
            case SDLK_s:
            case SDLK_a:
            case SDLK_d:
              graphicsCore.handleCameraMove(event.key.keysym.sym);
                  break;
          }
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
    graphicsCore.render(objects);
    SDL_Delay(1000/60);
  }*/

  std::vector<GraphicsModel*> objects;


  prepareSimulation();

  auto simObjects = simulation->getObjects();
  objects.reserve(simObjects.size());
  for (auto object : simObjects) {
    objects.emplace_back(dynamic_cast<PGRsim::SimpleObject *>(object)->getObjectModel());
  }

  auto model = SimpleGraphicsModel::LoadFromOBJ("small_ball.obj");
  model->setPosition(graphicsCore.getLightPos());
  objects.emplace_back(model);

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
              simObjects[0]->setCurrentPosition(simObjects[0]->getCurrectPosition() + glm::vec3(-0.05f, 0, 0));
              break;
            case SDLK_RIGHT:
              simObjects[0]->setCurrentPosition(simObjects[0]->getCurrectPosition() + glm::vec3(0.05f, 0, 0));
              break;
            case SDLK_UP:
              simObjects[0]->setCurrentPosition(simObjects[0]->getCurrectPosition() + glm::vec3(0, 0.05f, 0));
              break;
            case SDLK_DOWN:
              simObjects[0]->setCurrentPosition(simObjects[0]->getCurrectPosition() + glm::vec3(0, -0.05f, 0));
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
    }

    graphicsCore.render(objects);
    SDL_Delay(1000/60);
  }

  graphicsCore.cleanup();

  return 0;
}
