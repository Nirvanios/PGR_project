// Headerphile.com OpenGL Tutorial part 2
// A simple example involving VBOs and a VAO to draw a simple square
// Source code is an adaption / simplicication of : https://www.opengl.org/wiki/Tutorial2:_VAOs,_VBOs,_Vertex_and_Fragment_Shaders_(C_/_SDL)

// Compile :
// 	clang++ main.cpp -lGL -lGLEW -lSDL2 -std=c++11 -o Test
// or
// 	g++ main.cpp -lGL -lGLEW -lSDL2 -std=c++11 -o Test
//
#include <iostream>

#include "shader.h"
#include "graphicObjects/SimpleGraphicsModelCreator.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Simulation.h>
#include <SimModel.h>
#include <GravityForce.h>
#include <DragForce.h>
#include "graphics/camera/Camera.h"

Camera camera;

int width = 1024, height = 640;

std::string programName = "Headerphile SDL2 - OpenGL thing";

// Our SDL_Window ( just like with SDL2 wihout OpenGL)
SDL_Window *mainWindow;

// Our opengl context handle
SDL_GLContext mainContext;

// Our object has 4 points
const uint32_t points = 4;

// Each color has 4 values ( red, green, blue, alpha )
const uint32_t floatsPerColor = 4;

const float sceneFloor[]={
        -100, -30, 100,
        -100, -30, -100,
        100, -30, 100,
        100, -30, -100
};

const unsigned char floorIndicies[] ={
        0, 1, 2,
        1, 2, 3
};

const float floorColor[] ={
        0.0, 1.0, 0.0, 1.0,
        0.0, 1.0, 0.0, 1.0,
        0.0, 1.0, 0.0, 1.0,
        0.0, 1.0, 0.0, 1.0
};

// This is the object we'll draw ( a simple square
float colors[] = {
    0.0, 1.0, 0.0, 1.0, // Top left
    1.0, 1.0, 0.0, 1.0,   // Top right
    1.0, 0.0, 0.0, 1.0,   // Bottom right
    0.0, 0.0, 1.0, 1.0}; // Bottom left;

// Create variables for storing the ID of our VAO and VBO
GLuint vao[1];

std::vector<GLuint> *vbo = new std::vector<GLuint>();
std::vector<GLuint> *vboC = new std::vector<GLuint>();
std::vector<GLuint> *ebo = new std::vector<GLuint>();

// The positons of the position and color data within the VAO
const uint32_t positionAttributeIndex = 0, colorAttributeIndex = 1;

// Our wrapper to simplify the shader code
Shader shader;

auto gravity = new GravityForce;
auto air = new DragForce();

bool SetOpenGLAttributes();
void PrintSDL_GL_Attributes();
void CheckSDLError(int line);

Uint32 Render(std::vector<SimpleGraphicsModel *> *objects) {
  // First, render a square without any colors ( all vertexes will be black )
  // ===================
  // Make our background grey
  glClearColor(0.5, 0.5, 0.5, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
  glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float) width / (float) height, 0.1f, 100.0f);



// Model matrix : an identity matrix (model will be at the origin)
  glm::mat4 Model = glm::mat4(1.0f);

// Our ModelViewProjection : multiplication of our 3 matrices
  glm::mat4
      mvp = Projection * camera.GetViewMatrix() * Model; // Remember, matrix multiplication is the other way around

  GLuint MatrixID = shader.getUniformLocation("mvp");
  glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

  glDisableVertexAttribArray(colorAttributeIndex);

  // Invoke glDrawArrays telling that our data is a line loop and we want to draw 2-4 vertexes
  int i = 0;
  for (auto item : *objects) {
    if (item->isLine()) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    glm::mat4 transform = glm::translate(Model, item->getPosition());

    glBindBuffer(GL_ARRAY_BUFFER, vbo->at(i));
    glBufferSubData(GL_ARRAY_BUFFER, 0, (item->getVerticesSize() * sizeof(float)), item->getVertices());
    glEnableVertexAttribArray(positionAttributeIndex);
    glVertexAttribPointer(positionAttributeIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo->at(i));
    // Specify that our coordinate data is going into attribute index 0, and contains three floats per vertex

    GLuint transformID = shader.getUniformLocation("translate");
    glUniformMatrix4fv(transformID, 1, GL_FALSE, &transform[0][0]);
    glDrawElements(GL_TRIANGLES, item->getIndiciesSize(), GL_UNSIGNED_BYTE, NULL);
    //glDisableVertexAttribArray(positionAttributeIndex);
    i++;

    if (item->isLine()) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
  }

    glBindBuffer(GL_ARRAY_BUFFER, vbo->back());
    glEnableVertexAttribArray(positionAttributeIndex);
    glVertexAttribPointer(positionAttributeIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, vboC->back());
    glEnableVertexAttribArray(colorAttributeIndex);
    glVertexAttribPointer(colorAttributeIndex, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo->back());
    GLuint transformID = shader.getUniformLocation("translate");
    glUniformMatrix4fv(transformID, 1, GL_FALSE, &Model[0][0]);
    glDrawElements(GL_TRIANGLES, sizeof(floorIndicies), GL_UNSIGNED_BYTE, NULL);


  // Swap our buffers to make our changes visible
  SDL_GL_SwapWindow(mainWindow);

}

Simulation *simulation;
void prepareSimulation() {
  simulation = new Simulation();

  auto cubePos = glm::vec3(0.1f, 0.3f, 0.3f);
  auto stationaryCubeSimObj = new SimModel(1000.0f,
                                           Passive, SimpleGraphicsModelCreator::CreateQuad(0.5f, 0.5f, 0.5f, 0, 0, 0));
  simulation->addObject(stationaryCubeSimObj);

  auto sphereMass = 1.0f;
  auto sphereAPos = glm::vec3(0, 0, 0);
  auto movingSphereSimObj = new SimModel(sphereMass,
                                         Active, SimpleGraphicsModelCreator::CreateQuad(0.3f, 0.3f, 0.3f, 1.0f, 0, 0));
  simulation->addObject(movingSphereSimObj);

  auto sphereBPos = glm::vec3(0.2f, 0, 0);
  auto movingSphereSimObj2 = new SimModel(sphereMass,
                                          Active, SimpleGraphicsModelCreator::CreateQuad(0.3f, 0.3f, 0.3f, 0.3f, 0, 0));
  simulation->addObject(movingSphereSimObj2);

  auto sphereCPos = glm::vec3(10.0f, 0, 0);
  auto movingSphereSimObj3 = new SimModel(sphereMass,
                                          Active, SimpleGraphicsModelCreator::CreateQuad(0.2f, 0.2f, 0.2f, 3.0f, 0, 0));
  simulation->addObject(movingSphereSimObj3);

  float stiffness = 8.0f;
  float damping = 0.1f;
  simulation->addSpring(stiffness, damping, stationaryCubeSimObj,
                        movingSphereSimObj);

  simulation->addSpring(stiffness, damping, movingSphereSimObj2,
                        movingSphereSimObj);

  simulation->addSpring(stiffness, damping, movingSphereSimObj3,
                        stationaryCubeSimObj);

  simulation->addGlobalForce(gravity);

  float dragCoefficient = 0.5f;
  air->setDragCoefficient(dragCoefficient);
  simulation->addGlobalForce(air);

  simulation->setConstraintIterations(0);
}

bool SetupBufferObjects(std::vector<SimpleGraphicsModel *> *objects) {

  GLuint tempVBO;

  // Generate and assign a Vertex Array Object to our handle
  glGenVertexArrays(1, vao);

  // Bind our Vertex Array Object as the current used object
  glBindVertexArray(vao[0]);

  // Positions
  // ===================
  // Bind our first VBO as being the active buffer and storing vertex attributes (coordinates)
  for (auto item : *objects) {
    glGenBuffers(1, &tempVBO);

    glBindBuffer(GL_ARRAY_BUFFER, tempVBO);
    vbo->push_back(tempVBO);


    // Copy the vertex data from diamond to our buffer
    glBufferData(GL_ARRAY_BUFFER, (item->getVerticesSize() * sizeof(float)), item->getVertices(),
                 GL_DYNAMIC_DRAW);

  }

    glGenBuffers(1, &tempVBO);
    glBindBuffer(GL_ARRAY_BUFFER, tempVBO);
    vbo->push_back(tempVBO);
    // Copy the vertex data from diamond to our buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(sceneFloor), sceneFloor,
                 GL_STATIC_DRAW);

  // Colors
  // =======================
  glGenBuffers(1, &tempVBO);
  glBindBuffer(GL_ARRAY_BUFFER, tempVBO);
  vboC->push_back(tempVBO);

  // Copy the vertex data from diamond to our buffer
  glBufferData(GL_ARRAY_BUFFER, sizeof(floorColor), floorColor, GL_STATIC_DRAW);

  // Specify that our coordinate data is going into attribute index 0, and contains three floats per vertex
  //glVertexAttribPointer(colorAttributeIndex, 4, GL_FLOAT, GL_FALSE, 0, 0);

  GLuint tempEBO;
  for (auto item : *objects) {
    glGenBuffers(1, &tempEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tempEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, item->getIndiciesSize(), item->getIndices(), GL_STATIC_DRAW);
    ebo->push_back(tempEBO);
  }

    glGenBuffers(1, &tempEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tempEBO);
    glVertexAttribPointer(colorAttributeIndex, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(floorIndicies), floorIndicies, GL_STATIC_DRAW);
    ebo->push_back(tempEBO);

  // Set up shader ( will be covered in the next part )
  // ===================
  if (!shader.Init())
    return false;

  shader.UseProgram();

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  return true;
}
bool Init() {
  // Initialize SDL's Video subsystem
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS) != 0) {
    std::cout << "Failed to init SDL\n";
    return false;
  }

  // Create our window centered at 512x512 resolution
  mainWindow = SDL_CreateWindow(programName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

  // Check that everything worked out okay
  if (!mainWindow) {
    std::cout << "Unable to create window\n" << std::endl;;
    CheckSDLError(__LINE__);
    return false;
  }

  SetOpenGLAttributes();

  // Create our opengl context and attach it to our window
  mainContext = SDL_GL_CreateContext(mainWindow);

  // This makes our buffer swap syncronized with the monitor's vertical refresh
  SDL_GL_SetSwapInterval(1);

  // Init GLEW
  glewExperimental = GL_TRUE;
  glewInit();

  camera.Position = glm::vec3(0, 0, 5);

  return true;
}

bool SetOpenGLAttributes() {
  // Set our OpenGL version.
  // SDL_GL_CONTEXT_CORE gives us only the newer version, deprecated functions are disabled
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  // 3.2 is part of the modern versions of OpenGL, but most video cards whould be able to run it
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

  // Turn on double buffering with a 24bit Z buffer.
  // You may need to change this to 16 or 32 for your system
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  return true;
}

void Cleanup() {
  // Cleanup all the things we bound and allocated
  shader.CleanUp();

  glDisableVertexAttribArray(0);
  //glDeleteBuffers(1, vbo);
  glDeleteVertexArrays(1, vao);

  // Delete our OpengL context
  SDL_GL_DeleteContext(mainContext);

  // Destroy our window
  SDL_DestroyWindow(mainWindow);

  // Shutdown SDL 2
  SDL_Quit();
}

void updateSimulation() {
  static SimTime simTime = 0.0f;
  simTime += 1 / 60.0f;
  simulation->update(simTime);
}

int main(int argc, char *argv[]) {

  if (!Init())
    return -1;

  // Clear our buffer with a grey background
  glClearColor(0.5, 0.5, 0.5, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  SDL_GL_SwapWindow(mainWindow);

  std::cout << "Seting up VBO + VAO..." << std::endl;

  auto objects = new std::vector<SimpleGraphicsModel *>();
  /* Width, Height, Depth, translate x, y, z*/
  //objects->push_back(SimpleGraphicsModelCreator::CreateQuad(1,1,1, 0,0,0));
  /* start point, end point*/

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

  if (!SetupBufferObjects(objects))
    return -1;

  std::cout << "Rendering..." << std::endl;

  bool is_running = true;
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
            SDL_GetWindowSize(mainWindow, &width, &height);
          glViewport(0, 0, width, height);
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
            case SDLK_w:camera.ProcessKeyboard(FORWARD, 0.1);
              break;
            case SDLK_s:camera.ProcessKeyboard(BACKWARD, 0.1);
              break;
            case SDLK_a:camera.ProcessKeyboard(LEFT, 0.1);
              break;
            case SDLK_d:camera.ProcessKeyboard(RIGHT, 0.1);
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
            case SDLK_p:if (air->getDragCoefficient() > 0.05f) {
              air->setDragCoefficient(air->getDragCoefficient() + 0.05f);
              }
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
            camera.ProcessMouseMovement(event.motion.xrel, event.motion.yrel, false);
          }
          break;
      }
    }

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

    Render(objects);
    SDL_Delay(16);
  }

  Cleanup();

  return 0;
}

void CheckSDLError(int line = -1) {
  std::string error = SDL_GetError();

  if (error != "") {
    std::cout << "SLD Error : " << error << std::endl;

    if (line != -1)
      std::cout << "\nLine : " << line << std::endl;

    SDL_ClearError();
  }
}

void PrintSDL_GL_Attributes() {
  int value = 0;
  SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &value);
  std::cout << "SDL_GL_CONTEXT_MAJOR_VERSION : " << value << std::endl;

  SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &value);
  std::cout << "SDL_GL_CONTEXT_MINOR_VERSION: " << value << std::endl;
}
