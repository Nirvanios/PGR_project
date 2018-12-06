#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Simulation.h>
#include <GravityForce.h>
#include <DragForce.h>
#include "third_party/Camera.h"
#include <springs/SnappableSpring.h>
#include <core/GraphicsCore.h>
#include <SimObject.h>
#include <SimpleObject.h>
#include <objects/GraphicsModel.h>
#include <objects/SimpleGraphicsModel.h>
#include <StdoutLogger.h>
#include <objects/ComplexGraphicsModel.h>
#include <ClothSim.h>
#include <ComplexObject.h>

auto gravity = new PGRsim::GravityForce;
auto air = new PGRsim::DragForce();

PGRsim::ClothSim simulation;

PGRsim::Constraint *movableConstraint;

void prepareSimulation() {
  simulation.setIntegrator(new PGRsim::VerletIntegrator(1 / 60.0f));

  simulation.prepareClothObject("big_cloth.obj");

  simulation.addGlobalForce(gravity);

  air->setDragCoefficient(0.5f);
  simulation.addGlobalForce(air);

  simulation.setConstraintIterations(10);

  movableConstraint =
      ((PGRsim::ComplexObject *) simulation.getObjects()[simulation.getObjects().size() - 1])->getConstraints()[0];

}

void updateSimulation() {
  static PGRsim::SimTime simTime = 0.0f;
  simTime += 1 / 60.0f;
  simulation.update(simTime);
}

int main(int argc, char *argv[]) {
  PGRgraphics::GraphicsCore graphicsCore;

  StdoutLogger::getInstance().logTime("Init graphics core");
  if (!graphicsCore.init())
    return -1;


  std::vector<PGRgraphics::GraphicsModel *> objects;

  StdoutLogger::getInstance().logTime("Prepare simulation");
  prepareSimulation();

  StdoutLogger::getInstance().logTime("Add objects");
  auto simObjects = simulation.getObjects();
  objects.reserve(simObjects.size());
  for (auto object : simObjects) {
    auto tempObject = dynamic_cast<PGRsim::SimObjectWithModel *>(object);
    if (tempObject != nullptr) {
      objects.emplace_back(tempObject->getObjectModel());
    }
  }

  /*auto model = PGRgraphics::ComplexGraphicsModel::LoadFromOBJ("simple_cloth.obj");
  objects.emplace_back(model);*/

  objects.emplace_back(PGRgraphics::SimpleGraphicsModel::LoadFromOBJ("floor.obj"));

  /*auto model2 = PGRgraphics::SimpleGraphicsModel::LoadFromOBJ("male_head.obj");
  model2->setPosition(glm::vec3(0, 0, -30));
  objects.emplace_back(model2);*/
  if (!graphicsCore.setupBufferObjects(objects))
    return -1;

  StdoutLogger::getInstance().logTime("Start main loop");

  bool is_running = true;
  bool is_simRunning = false;
  bool enableCameraMovement = false;
  bool gravityEnabled = true;
  int selectedObject = 0;
  SDL_Event event;

  uint32_t time1 = 0;
  uint32_t time2;
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
              ((PGRsim::PointConstraint *) movableConstraint)->setPosition(
                  ((PGRsim::PointConstraint *) movableConstraint)->getPosition() + glm::vec3(-0.05f, 0, 0));
              //simObjects[0]->setCurrentPosition(simObjects[0]->getCurrectPosition() + glm::vec3(-0.05f, 0, 0));
              break;
            case SDLK_RIGHT:
              ((PGRsim::PointConstraint *) movableConstraint)->setPosition(
                  ((PGRsim::PointConstraint *) movableConstraint)->getPosition() + glm::vec3(0.05f, 0, 0));
              //simObjects[0]->setCurrentPosition(simObjects[0]->getCurrectPosition() + glm::vec3(0.05f, 0, 0));
              break;
            case SDLK_UP:
              ((PGRsim::PointConstraint *) movableConstraint)->setPosition(
                  ((PGRsim::PointConstraint *) movableConstraint)->getPosition() + glm::vec3(0, 0.05f, 0));
              //simObjects[0]->setCurrentPosition(simObjects[0]->getCurrectPosition() + glm::vec3(0, 0.05f, 0));
              break;
            case SDLK_DOWN:
              ((PGRsim::PointConstraint *) movableConstraint)->setPosition(
                  ((PGRsim::PointConstraint *) movableConstraint)->getPosition() + glm::vec3(0, -0.05f, 0));
              //simObjects[0]->setCurrentPosition(simObjects[0]->getCurrectPosition() + glm::vec3(0, -0.05f, 0));
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
            case SDLK_o:if (air->getDragCoefficient() > 0.2f) {
                air->setDragCoefficient(air->getDragCoefficient() - 0.05f);
              }
              break;
            case SDLK_p:
              air->setDragCoefficient(air->getDragCoefficient() + 0.05f);
              break;
              case SDLK_n:
                graphicsCore.handleModelFill();
                break;
              case SDLK_m:
                graphicsCore.handleModelWireframe();
                break;
            case SDLK_SPACE: is_simRunning = !is_simRunning;
              break;
          }
          break;
        case SDL_MOUSEWHEEL:
          graphicsCore.handleMouseWheel(event.wheel.y);
          break;
        case SDL_MOUSEBUTTONDOWN:
          if (event.button.button == SDL_BUTTON_LEFT) {
            enableCameraMovement = true;
          }
          else if(event.button.button == SDL_BUTTON_RIGHT){
            selectedObject = graphicsCore.selectObject(event.button.x, event.button.y, objects);
          }
          break;
        case SDL_MOUSEBUTTONUP:
          if (event.button.button == SDL_BUTTON_LEFT) {
            enableCameraMovement = false;
          }
        case SDL_MOUSEMOTION:
          if (enableCameraMovement) {
            graphicsCore.handleMouseMove(event.motion.xrel, event.motion.yrel);
          }
          break;
      }
    }

    time2 = SDL_GetTicks();
    if (time2 - time1 > 16) {
      time1 = time2;
      graphicsCore.render(objects);
      if (is_simRunning) {
        updateSimulation();
      }
    }
    SDL_Delay(1);
  }

  return 0;
}
