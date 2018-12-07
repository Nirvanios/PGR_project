//
// Created by kuro on 2.12.18.
//


#include <SDL.h>
#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <StdoutLogger.h>
#include "SimpleGraphicsModel.h"
#include "GraphicsCore.h"

bool PGRgraphics::GraphicsCore::init() {
  // Initialize SDL's Video subsystem
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
    std::cout << "Failed to init SDL\n";
    return false;
  }

  StdoutLogger::getInstance().logTime("SDL: set attributes");

  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

  std::string logMsg = std::string("SDL: window size: " + std::to_string(width) + "x" + std::to_string(height));
  StdoutLogger::getInstance().logTime(logMsg);
  mainWindow = SDL_CreateWindow(programName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

  if (!mainWindow) {
    std::cout << "Unable to create window\n" << std::endl;
    checkSDLError(__LINE__);
    return false;
  }
  StdoutLogger::getInstance().logTime("SDL: window created");

  setOpenGLAttributes();

  // Create our opengl context and attach it to our window
  mainContext = SDL_GL_CreateContext(mainWindow);

  SDL_GL_SetSwapInterval(1);

  StdoutLogger::getInstance().logTime("Init glew");
  glewExperimental = GL_TRUE;
  glewInit();

  StdoutLogger::getInstance().logTime("Set camera to 0, 0, 10");
  camera.Position = glm::vec3(0, 0, 10);
  camera.MovementSpeed = 1.0f;

  // Clear our buffer with a grey background
  glClearColor(0.5, 0.5, 0.5, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  /*glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);
  glFrontFace(GL_CW);*/
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glEnable(GL_MULTISAMPLE);

  return true;
}

bool PGRgraphics::GraphicsCore::setOpenGLAttributes() {
  // Set our OpenGL version.
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  return true;
}

void PGRgraphics::GraphicsCore::checkSDLError(int line = -1) {
  std::string error = SDL_GetError();

  if (!error.empty()) {
    std::cerr << "SLD Error : " << error << std::endl;

    if (line != -1)
      std::cerr << "\nLine : " << line << std::endl;

    SDL_ClearError();
  }
}

bool PGRgraphics::GraphicsCore::setupBufferObjects(std::vector<GraphicsModel *> &objects) {

  GLuint tempVBO;

  glGenVertexArrays(1, vao);

  glBindVertexArray(vao[0]);

  // Positions
  // ===================
  // Bind our first VBO as being the active buffer and storing vertex attributes (coordinates)
  int i = 0;
  for (auto item : objects) {
    glGenBuffers(1, &tempVBO);

    glBindBuffer(GL_ARRAY_BUFFER, tempVBO);
    vbo.push_back(tempVBO);
    // Copy the vertex data from diamond to our buffer
    glBufferData(GL_ARRAY_BUFFER,
                 (item->getVertices().size() * 3 * sizeof(float)),
                 item->getVertices().data(),
                 GL_DYNAMIC_DRAW);
    colorIDs.emplace_back(getIDColor(i));
    i++;
  }

  GLuint tempEBO;
  for (auto item : objects) {
    glGenBuffers(1, &tempEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tempEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 item->getVertexIndices().size() * sizeof(int),
                 item->getVertexIndices().data(),
                 GL_DYNAMIC_DRAW);
    ebo.push_back(tempEBO);
  }

  GLuint tempNBO;
  for (auto item : objects) {
    glGenBuffers(1, &tempNBO);
    glBindBuffer(GL_ARRAY_BUFFER, tempNBO);
    glBufferData(GL_ARRAY_BUFFER,
                 item->getNormals().size() * sizeof(float),
                 item->getNormals().data(),
                 GL_DYNAMIC_DRAW);
    nbo.push_back(tempNBO);
  }

  // Set up shader ( will be covered in the next part )
  // ===================
  if (!shader.Init())
    return false;

  shader.UseProgram();

  modelViewGLUniform = shader.getUniformLocation("modelview");
  projGLUniform = shader.getUniformLocation("projection");
  lightPosUniform = shader.getUniformLocation("lightPos");
  inputColorUniform = shader.getUniformLocation("inputColor");
  selectUniform = shader.getUniformLocation("select");
  cameraPosUniform = shader.getUniformLocation("cameraPos");

  return true;
}

void PGRgraphics::GraphicsCore::render(std::vector<GraphicsModel *> &objects, bool selectRender) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float) width / (float) height, 0.1f, 100.0f);

  glm::mat4 Model = glm::mat4(1.0f);

  glm::mat4 modelView = camera.GetViewMatrix() * Model;

  glUniform3fv(lightPosUniform, 1, glm::value_ptr(lightPos));
  glUniformMatrix4fv(projGLUniform, 1, GL_FALSE, glm::value_ptr(Projection));
  glUniform3fv(cameraPosUniform, 1, glm::value_ptr(camera.Position));




  // Invoke glDrawArrays telling that our data is a line loop and we want to draw 2-4 vertexes
  int i = 0;
  for (auto item : objects) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
    if (dynamic_cast<SimpleGraphicsModel *>(item) != nullptr) {
      modelView =
          camera.GetViewMatrix() * Model *
              reinterpret_cast<SimpleGraphicsModel *>(item)->getTranslationMatrix();
    } else {
      modelView = camera.GetViewMatrix() * Model;
      glBufferSubData(GL_ARRAY_BUFFER, 0,
                      (item->getVertices().size() * 3 * sizeof(float)),
                      item->getVertices().data());
    }

    glUniformMatrix4fv(modelViewGLUniform, 1, GL_FALSE, glm::value_ptr(modelView));

    glEnableVertexAttribArray(positionAttributeIndex);
    glVertexAttribPointer(positionAttributeIndex, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, nbo[i]);
    if (dynamic_cast<SimpleGraphicsModel *>(item) == nullptr) {
      glBufferSubData(GL_ARRAY_BUFFER, 0, (item->getNormals().size() * 3 * sizeof(float)),
                      item->getNormals().data());
    }
    glEnableVertexAttribArray(normalAttributeIndex);
    glVertexAttribPointer(normalAttributeIndex, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    if (!selectRender) {
      glUniform3fv(inputColorUniform, 1, glm::value_ptr(item->getColor()));
      glUniform1i(selectUniform, 0);
    } else {
      glUniform3fv(inputColorUniform, 1, glm::value_ptr(colorIDs[i]));
      glUniform1i(selectUniform, 1);
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i]);
    if (dynamic_cast<SimpleGraphicsModel *>(item) == nullptr) {
      glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, item->getVertexIndices().size() * sizeof(int),
                      item->getVertexIndices().data());
    }
    // Specify that our coordinate data is going into attribute index 0, and contains three floats per vertex

    glDrawElements(GL_TRIANGLES, item->getVertexIndices().size() * sizeof(int), GL_UNSIGNED_INT, nullptr);
    i++;
  }

  if (!selectRender) {
    SDL_GL_SwapWindow(mainWindow);
  }
}

void PGRgraphics::GraphicsCore::cleanup() {
  // Cleanup all the things we bound and allocated
  shader.CleanUp();

  glDisableVertexAttribArray(0);

  deleteBuffers(vbo);
  deleteBuffers(ebo);

  glDeleteVertexArrays(1, vao);

  // Delete our OpengL context
  SDL_GL_DeleteContext(mainContext);

  // Destroy our window
  SDL_DestroyWindow(mainWindow);

  // Shutdown SDL 2
  SDL_Quit();
}

void PGRgraphics::GraphicsCore::deleteBuffers(std::vector<GLuint> &buff) {
  int i = 0;
  for (auto item : buff) {
    glDeleteBuffers(i, &item);
    i++;
  }
}

void PGRgraphics::GraphicsCore::handleResize() {
    SDL_GL_GetDrawableSize(mainWindow, &width, &height);
  glViewport(0, 0, width, height);
}

void PGRgraphics::GraphicsCore::handleCameraMove(SDL_Keycode key) {
  switch (key) {
    case SDLK_w:camera.ProcessKeyboard(FORWARD, 1);
      break;
    case SDLK_s:camera.ProcessKeyboard(BACKWARD, 1);
      break;
    case SDLK_a:camera.ProcessKeyboard(LEFT, 1);
      break;
    case SDLK_d:camera.ProcessKeyboard(RIGHT, 1);
      break;
  }

}

void PGRgraphics::GraphicsCore::handleMouseMove(float xoffset, float yoffset) {
  camera.ProcessMouseMovement(xoffset, yoffset, false);
}

const glm::vec3 &PGRgraphics::GraphicsCore::getLightPos() const {
  return lightPos;
}

void PGRgraphics::GraphicsCore::setLightPos(const glm::vec3 &lightPos) {
  GraphicsCore::lightPos = lightPos;
}

void PGRgraphics::GraphicsCore::handleMouseWheel(float yOffset) {
  camera.ProcessMouseScroll(yOffset);
}

PGRgraphics::GraphicsCore::~GraphicsCore() {
  cleanup();
}

void PGRgraphics::GraphicsCore::handleModelFill() {
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void PGRgraphics::GraphicsCore::handleModelWireframe() {
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void PGRgraphics::GraphicsCore::handleSelectObject(int x, int y, std::vector<GraphicsModel *> &objects) {
  glDisable(GL_MULTISAMPLE);
  render(objects, true);
  glEnable(GL_MULTISAMPLE);

  glFlush();
  glFinish();

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  unsigned char data[4];
  glReadPixels(x, height - y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);

  int id = data[0] + (data[1] >> 8) + (data[2] >> 16);

  if (id <= objects.size()) {
    auto foundObject = std::find_if(selectedObjects.begin(), selectedObjects.end(), [id](selectedObject i)-> bool {return i.objectId == id;});
      if(foundObject == selectedObjects.end()){
        selectedObjects.emplace_back(selectedObject{.objectId = id,
                                                    .previousColor = objects[id]->getColor()});
        objects[id]->setColor(glm::vec3(1, 0, 0));
      }
      else{
        objects[id]->setColor(foundObject.base()->previousColor);
        selectedObjects.erase(foundObject);
      }
  }
}

glm::vec3 PGRgraphics::GraphicsCore::getIDColor(GLuint ID) {
  return glm::vec3(static_cast<float>(((ID & 0x000000FF)) / 255.0),
                   static_cast<float>(((ID & 0x0000FF00) >> 8) / 255.0),
                   static_cast<float>(((ID & 0x00FF0000) >> 16) / 255.0));
}

const std::vector<PGRgraphics::GraphicsCore::selectedObject> &PGRgraphics::GraphicsCore::getSelectedObjects() const {
  return selectedObjects;
}

void PGRgraphics::GraphicsCore::clearSelectedObjects(std::vector<PGRgraphics::GraphicsModel *> &objects) {
  for(auto item : selectedObjects){
    objects[item.objectId]->setColor(item.previousColor);
  }
  selectedObjects.clear();
}

