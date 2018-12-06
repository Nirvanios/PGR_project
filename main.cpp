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

bool tearDemo = false;

PGRsim::ClothSim simulation;

std::vector<PGRsim::PointConstraint *> constraints;
std::vector<int> constraintModelIDs;

std::vector<PGRgraphics::GraphicsModel *> objects;

void prepareSimulation() {
  simulation.setIntegrator(new PGRsim::VerletIntegrator(1 / 60.0f));

  simulation.prepareClothObject("medium_cloth.obj");

  simulation.addGlobalForce(gravity);

  air->setDragCoefficient(0.5f);
  simulation.addGlobalForce(air);

  simulation.setConstraintIterations(10);

  constraints.emplace_back(
      (PGRsim::PointConstraint *) ((PGRsim::ComplexObject *) simulation.getObjects()[simulation.getObjects().size()
          - 1])->getConstraints()[0]);

  constraints.emplace_back(
      (PGRsim::PointConstraint *) ((PGRsim::ComplexObject *) simulation.getObjects()[simulation.getObjects().size()
          - 1])->getConstraints()[1]);

  simulation.prepareClothObject("big_cloth.obj");

  constraints.emplace_back(
      (PGRsim::PointConstraint *) ((PGRsim::ComplexObject *) simulation.getObjects()[simulation.getObjects().size()
          - 1])->getConstraints()[0]);

  constraints.emplace_back(
      (PGRsim::PointConstraint *) ((PGRsim::ComplexObject *) simulation.getObjects()[simulation.getObjects().size()
          - 1])->getConstraints()[1]);

  constraints.emplace_back(
      (PGRsim::PointConstraint *) ((PGRsim::ComplexObject *) simulation.getObjects()[simulation.getObjects().size()
          - 1])->getConstraints()[2]);

  constraints.emplace_back(
      (PGRsim::PointConstraint *) ((PGRsim::ComplexObject *) simulation.getObjects()[simulation.getObjects().size()
          - 1])->getConstraints()[3]);

}

void updateSimulation() {
  static PGRsim::SimTime simTime = 0.0f;
  simTime += 1 / 60.0f;
  if (tearDemo) {
    simulation.tear();
  }
  simulation.update(simTime);
}

enum Dir {
  Left, Right, Up, Down
};

void handleMovement(std::vector<int> &selectedObjects, Dir direction) {
  if (selectedObjects.empty()) {
    return;
  }

  for (auto selectedObject : selectedObjects) {
    auto res = std::find(constraintModelIDs.begin(), constraintModelIDs.end(), selectedObject);
    if (res != std::end(constraintModelIDs)) {
      long index = std::distance(constraintModelIDs.begin(), res);
      switch (direction) {
        case Left:constraints[index]->setPosition(constraints[index]->getPosition() + glm::vec3(-0.05f, 0, 0));
          break;
        case Right:constraints[index]->setPosition(constraints[index]->getPosition() + glm::vec3(0.05f, 0, 0));
          break;
        case Up:constraints[index]->setPosition(constraints[index]->getPosition() + glm::vec3(0, 0.05f, 0));
          break;
        case Down:constraints[index]->setPosition(constraints[index]->getPosition() + glm::vec3(0, -0.05f, 0));
          break;
      }
      dynamic_cast<PGRgraphics::SimpleGraphicsModel *>(objects[*res])->setPosition(constraints[index]->getPosition());
    }
  }
}

void handleMovement(std::vector<int> &selectedObjects, float x, float y) {
  if (selectedObjects.empty()) {
    return;
  }

  for (auto selectedObject : selectedObjects) {
    auto res = std::find(constraintModelIDs.begin(), constraintModelIDs.end(), selectedObject);
    if (res != std::end(constraintModelIDs)) {
      long index = std::distance(constraintModelIDs.begin(), res);
      constraints[index]->setPosition(constraints[index]->getPosition() + glm::vec3(x, y, 0));

      dynamic_cast<PGRgraphics::SimpleGraphicsModel *>(objects[*res])->setPosition(constraints[index]->getPosition());
    }
  }
}

int main(int argc, char *argv[]) {
  PGRgraphics::GraphicsCore graphicsCore;

  StdoutLogger::getInstance().logTime("Init graphics core");
  if (!graphicsCore.init())
    return -1;

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

  for (int i = 0; i < constraints.size(); i++) {
    constraintModelIDs.emplace_back(objects.size());
    auto model = PGRgraphics::SimpleGraphicsModel::LoadFromOBJ("smaller_ball.obj");
    model->setPosition(constraints[i]->getPosition());
    objects.emplace_back(model);
  }

  objects.emplace_back(PGRgraphics::SimpleGraphicsModel::LoadFromOBJ("floor.obj"));

  if (!graphicsCore.setupBufferObjects(objects))
    return -1;

  StdoutLogger::getInstance().logTime("Start main loop");

  bool is_running = true;
  bool is_simRunning = false;
  bool enableCameraMovement = false;
  bool gravityEnabled = true;
  bool moveWithCamera = false;
  std::vector<int> selectedObjects;
  SDL_Event event;

  uint32_t time1 = 0;
  uint32_t time2;

  bool updatedSim = false;
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
            case SDLK_LEFT:handleMovement(selectedObjects, Left);
              break;
            case SDLK_RIGHT:handleMovement(selectedObjects, Right);
              break;
            case SDLK_UP:handleMovement(selectedObjects, Up);
              break;
            case SDLK_DOWN:handleMovement(selectedObjects, Down);
              break;
            case SDLK_w:
            case SDLK_s:
            case SDLK_a:
            case SDLK_d:
              graphicsCore.handleCameraMove(event.key.keysym.sym);
              break;
            case SDLK_r:selectedObjects.clear();
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
            case SDLK_t:
              if (tearDemo == true) {
                simulation.stopTearDemo();
              }
              tearDemo = true;
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
            moveWithCamera = true;
            auto tmp = graphicsCore.selectObject(event.button.x, event.button.y, objects);
            if (tmp != -1) {
              selectedObjects.emplace_back(tmp);
            }
          }
          break;
        case SDL_MOUSEBUTTONUP:
          if (event.button.button == SDL_BUTTON_LEFT) {
            enableCameraMovement = false;
          } else if (event.button.button == SDL_BUTTON_RIGHT) {
            moveWithCamera = false;
          }
        case SDL_MOUSEMOTION:
          if (enableCameraMovement) {
            graphicsCore.handleMouseMove(event.motion.xrel, event.motion.yrel);
          } else if (moveWithCamera) {
            handleMovement(selectedObjects, event.motion.xrel / 100.0f, -event.motion.yrel / 100.0f);
          }
          break;
      }
    }

    time2 = SDL_GetTicks();

    if (!updatedSim) {
      if (is_simRunning) {
        updateSimulation();
      }
      updatedSim = true;
    }

    if (time2 - time1 > 16) {
      time1 = time2;
      graphicsCore.render(objects);
      updatedSim = false;
    }
    SDL_Delay(1);
  }

  return 0;
}
