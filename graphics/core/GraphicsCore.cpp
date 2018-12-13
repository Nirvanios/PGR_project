//
// Created by Igor Frank on 2.12.18.
//


#include <SDL.h>
#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <StdoutLogger.h>
#include <SDL_opengl.h>
#include "SimpleGraphicsModel.h"
#include "GraphicsCore.h"

bool PGRgraphics::GraphicsCore::init() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
    std::cout << "Failed to init SDL\n";
    return false;
  }

  StdoutLogger::getInstance().logTime(const_cast<char *>("SDL: set attributes"));

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
  StdoutLogger::getInstance().logTime(const_cast<char *>("SDL: window created"));

  setOpenGLAttributes();

  // Create our openGL context
  mainContext = SDL_GL_CreateContext(mainWindow);

  SDL_GL_SetSwapInterval(1);

  StdoutLogger::getInstance().logTime(const_cast<char *>("Init glew"));
  glewExperimental = GL_TRUE;
  glewInit();

  StdoutLogger::getInstance().logTime(const_cast<char *>("Set camera to 0, 0, 10"));
  camera.Position = glm::vec3(0, 0, 10);
  camera.MovementSpeed = 1.0f;

  // Clear our buffer with a grey background
  glClearColor(0.5, 0.5, 0.5, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  // Setup GL rendering properties
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

  GLuint tempVBO; //Vertex Buffer Objects
  GLuint tempEBO; //Element Buffer Objects
  GLuint tempNBO; //Normals Buffer Objects
  GLuint tempTBO; //Texture coordinates Buffer Objects
  GLuint tempETBO; //Unifrom Texture Files

  glGenVertexArrays(1, vao);

  glBindVertexArray(vao[0]);




  int i = 0;
  for (auto item : objects) {
      /*
       * Positions buffer
       * */
      glGenBuffers(1, &tempVBO);
      glBindBuffer(GL_ARRAY_BUFFER, tempVBO);
      vbo.push_back(tempVBO);
      glBufferData(GL_ARRAY_BUFFER,
                   item->getVertices().size() * 3 * sizeof(float),
                   item->getVertices().data(),
                   GL_DYNAMIC_DRAW);
      colorIDs.emplace_back(getIDColor(i));

      /*
       * Indices (element) buffer
       * */
      glGenBuffers(1, &tempEBO);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tempEBO);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                   item->getVertexIndices().size() * sizeof(int),
                   item->getVertexIndices().data(),
                   GL_DYNAMIC_DRAW);
      ebo.push_back(tempEBO);

      /*
       * Normals buffer
       * */
      glGenBuffers(1, &tempNBO);
      glBindBuffer(GL_ARRAY_BUFFER, tempNBO);
      glBufferData(GL_ARRAY_BUFFER,
                   item->getNormals().size() * sizeof(float),
                   item->getNormals().data(),
                   GL_DYNAMIC_DRAW);
      nbo.push_back(tempNBO);

      /*
       * Texture coordinates buffer
       * */
      if (item->getTextureFile() != nullptr) {
          glGenBuffers(1, &tempTBO);
          glBindBuffer(GL_ARRAY_BUFFER, tempTBO);
          glBufferData(GL_ARRAY_BUFFER,
                       item->getTexCoords().size() * sizeof(float),
                       item->getTexCoords().data(),
                       GL_STATIC_DRAW);
          tbo.push_back(tempTBO);
      }

      /*
       * Uniform texture file
       * */
      if (item->getTextureFile() != nullptr) {
          glGenTextures(1, &tempETBO);
          glBindTexture(GL_TEXTURE_2D, tempETBO);
          glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
          glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, item->getTextureFile()->w, item->getTextureFile()->h, 0, GL_RGB,
                       GL_UNSIGNED_BYTE, item->getTextureFile()->pixels);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
          glGenerateMipmap(GL_TEXTURE_2D);
          textures.emplace_back(tempETBO);
      }
      i++;
  }



  // Set up shader
  if (!shader.Init())
    return false;

  shader.UseProgram();

  modelViewGLUniform = shader.getUniformLocation("modelview");
  projGLUniform = shader.getUniformLocation("projection");
  lightPosUniform = shader.getUniformLocation("lightPos");
  inputColorUniform = shader.getUniformLocation("inputColor");
  selectUniform = shader.getUniformLocation("select");
  cameraPosUniform = shader.getUniformLocation("cameraPos");
  textureUniform = shader.getUniformLocation("tex");

  return true;
}

void PGRgraphics::GraphicsCore::render(std::vector<GraphicsModel *> &objects, bool selectRender) {
    // No color indicates usage of texture
    glm::vec3 noColor =  glm::vec3(-1, -1, -1);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float) width / (float) height, 0.1f, 100.0f);

  glm::mat4 Model = glm::mat4(1.0f);

  glm::mat4 modelView = camera.GetViewMatrix() * Model;

  glUniform3fv(lightPosUniform, 1, glm::value_ptr(lightPos));
  glUniformMatrix4fv(projGLUniform, 1, GL_FALSE, glm::value_ptr(Projection));
  glUniform3fv(cameraPosUniform, 1, glm::value_ptr(camera.Position));




  // Render loop over all models
  int i = 0; //model index
  int t = 0; //texture objects index
  for (auto item : objects) {
      //bind position buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);

      //if simple model (not cloth) use translation
    if (dynamic_cast<SimpleGraphicsModel *>(item) != nullptr) {
      modelView =
          camera.GetViewMatrix() * Model *
              reinterpret_cast<SimpleGraphicsModel *>(item)->getTranslationMatrix();
    }
    //Else reload vertices, after simulation changes them
    else {
      modelView = camera.GetViewMatrix() * Model;
      glBufferData(GL_ARRAY_BUFFER,
                   item->getVertices().size() * 3 * sizeof(float),
                   item->getVertices().data(),
                   GL_DYNAMIC_DRAW);
    }
        //Position attribute
      glEnableVertexAttribArray(positionAttributeIndex);
      glVertexAttribPointer(positionAttributeIndex, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

      //bind uniform MV matrix
    glUniformMatrix4fv(modelViewGLUniform, 1, GL_FALSE, glm::value_ptr(modelView));


    //Bind normals buffer
    glBindBuffer(GL_ARRAY_BUFFER, nbo[i]);

    //if not simple object (is cloth) reload normals
    if (dynamic_cast<SimpleGraphicsModel *>(item) == nullptr) {
      glBufferSubData(GL_ARRAY_BUFFER, 0, (item->getNormals().size() * 3 * sizeof(float)),
                      item->getNormals().data());
    }
    glEnableVertexAttribArray(normalAttributeIndex);
    glVertexAttribPointer(normalAttributeIndex, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    //if classic rendering to SDL window
    if (!selectRender) {
        //Bind uiform cloor if no texture
      if(item->getTextureFile() == 0) {
        glUniform3fv(inputColorUniform, 1, glm::value_ptr(item->getColor()));
        glUniform1i(selectUniform, 0);
      }
      //else bind texture
      else{
          glActiveTexture(GL_TEXTURE0);
        glBindBuffer(GL_ARRAY_BUFFER, tbo[t]);
        glUniform1i(textureUniform, 0);
        glEnableVertexAttribArray(textureCoordAttributeIndex);
        glVertexAttribPointer(textureCoordAttributeIndex, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
        glBindTexture(GL_TEXTURE_2D, textures[t]);
          glUniform3fv(inputColorUniform, 1, glm::value_ptr(noColor));
          glUniform1i(selectUniform, 0);
        t++;
      }
    } else { //if selecting model render each object with different color
      glUniform3fv(inputColorUniform, 1, glm::value_ptr(colorIDs[i]));
      glUniform1i(selectUniform, 1);
    }

    //Bind buffer with indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i]);
    if (dynamic_cast<SimpleGraphicsModel *>(item) == nullptr) { // reloading indices because of tearing
      glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, item->getVertexIndices().size() * sizeof(int),
                      item->getVertexIndices().data());
    }

    glDrawElements(GL_TRIANGLES, item->getVertexIndices().size() * sizeof(int), GL_UNSIGNED_INT, nullptr);
    i++;
  }

  if (!selectRender) {
    SDL_GL_SwapWindow(mainWindow);
  }
}

void PGRgraphics::GraphicsCore::cleanup() {
  shader.CleanUp();

  glDisableVertexAttribArray(0);

  glDeleteBuffers(vbo.size(), vbo.data());
  glDeleteBuffers(ebo.size(), ebo.data());
glDeleteBuffers(nbo.size(), nbo.data());
 glDeleteBuffers(tbo.size(), tbo.data());
  glDeleteTextures(textures.size(), textures.data());

  glDeleteVertexArrays(1, vao);

  shader.CleanUp();

  SDL_GL_DeleteContext(mainContext);

  SDL_DestroyWindow(mainWindow);

  SDL_Quit();
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
    //Render each object with specific color
  glDisable(GL_MULTISAMPLE);
  render(objects, true);
  glEnable(GL_MULTISAMPLE);

  //wait for GPU to process all work
  glFlush();
  glFinish();

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  unsigned char data[4];
  glReadPixels(x, height - y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);

  int id = data[0] + (data[1] >> 8) + (data[2] >> 16);

  if (id < objects.size()) { // if not background
    auto foundObject = std::find_if(selectedObjects.begin(),
                                    selectedObjects.end(),
                                    [id](selectedObject i) -> bool { return i.objectId == id; });
    if (foundObject == selectedObjects.end()) { //if already selected restore color and remove from selected
      selectedObjects.emplace_back(selectedObject{.objectId = id,
          .previousColor = objects[id]->getColor()});
      objects[id]->setColor(glm::vec3(1, 0, 0));
    } else { // else color it red and add to selected objects
      objects[id]->setColor(foundObject.base()->previousColor);
      selectedObjects.erase(foundObject);
    }
  }
}

//encode ID as color
glm::vec3 PGRgraphics::GraphicsCore::getIDColor(GLuint ID) {
  return glm::vec3(static_cast<float>(((ID & 0x000000FF)) / 255.0),
                   static_cast<float>(((ID & 0x0000FF00) >> 8) / 255.0),
                   static_cast<float>(((ID & 0x00FF0000) >> 16) / 255.0));
}

const std::vector<PGRgraphics::GraphicsCore::selectedObject> &PGRgraphics::GraphicsCore::getSelectedObjects() const {
  return selectedObjects;
}

void PGRgraphics::GraphicsCore::clearSelectedObjects(std::vector<PGRgraphics::GraphicsModel *> &objects) {
  for (auto item : selectedObjects) {
    objects[item.objectId]->setColor(item.previousColor);
  }
  selectedObjects.clear();
}

