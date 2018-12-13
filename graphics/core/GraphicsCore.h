//
// Created by Igor Frank on 2.12.18.
//

#ifndef PGR_PROJECT_GRAPHICSCORE_H
#define PGR_PROJECT_GRAPHICSCORE_H

#include "../../third_party/Camera.h"
#include <objects/GraphicsModel.h>
#include "Shader.h"

namespace PGRgraphics {
/**
 * Class for setting up openGL and rendering models
 *
 * @author Igor Frank
 */
class GraphicsCore {
 private:

  GLint projGLUniform;
  GLint modelViewGLUniform;
  GLint lightPosUniform;
  GLuint inputColorUniform;
  GLuint selectUniform;
  GLuint cameraPosUniform;
  GLuint textureUniform;

  std::string programName;
  SDL_Window *mainWindow;
  SDL_GLContext mainContext;
  int width = 1200, height = 700;
  Camera camera;
  Shader shader;

 public:
  struct selectedObject {
    int objectId;
    glm::vec3 previousColor;
  };

  const std::vector<selectedObject> &getSelectedObjects() const;

 private:
  std::vector<selectedObject> selectedObjects; /**< Selected objects*/

  const GLuint positionAttributeIndex = 0, normalAttributeIndex = 1, textureCoordAttributeIndex = 2;

  GLuint vao[1];
  std::vector<GLuint> vbo; /**< Vertices */
  std::vector<GLuint> tbo; /**< Textures coordinates*/
  std::vector<GLuint> ebo; /**< Indices */
  std::vector<GLuint> nbo; /**< Normals */
  std::vector<GLuint> textures; /**< Texture files*/
  std::vector<glm::vec3> colorIDs;

  glm::vec3 lightPos = glm::vec3(3.0f, 5.0f, 0.0f);

 private:
  /**
   * Frees up resources
   */
  void cleanup();

  /**
   * Prints what error happend
   * @param line number of line
   */
  void checkSDLError(int line);

  /**
   * Sets inital openGL attribues as version, etc.
   *
   */
  void setOpenGLAttributes();

  /**
   * generates color based on ID (integer)
   * @param ID ID to convert
   * @return encoded color
   */
  glm::vec3 getIDColor(GLuint ID);

 public:
  /**
   * Default constructor
   */
  GraphicsCore() = default;

  /**
   * Default destructor
   */
  virtual ~GraphicsCore();

  /**
   * Initialize SDL window, glew and openGL
   * @return true if no error else false
   */
  bool init();

  /**
   * Loads models to GPU buffers, and initialize shaders
   * @param objects models to load
   * @return true if no error else false
   */
  bool setupBufferObjects(std::vector<GraphicsModel *> &objects);

  /**
   * Renders all provided models
   * @param objects models to render
   * @param selectRender true if rendering for selection else false
   */
  void render(std::vector<GraphicsModel *> &objects, bool selectRender = false);

  /**
   * Handles window resize
   */
  void handleResize();

  /**
   * Handles camera movement
   * @param key pressed key(w,s,a,d)
   */
  void handleCameraMove(SDL_Keycode key);

  /**
   * Handles mouse drag
   * @param xoffset x offset of mouse movement
   * @param yoffset y offset of mouse movement
   */
  void handleMouseMove(float xoffset, float yoffset);

  /**
   * Handle mouse wheel
   * @param yOffset movement offset
   */
  void handleMouseWheel(float yOffset);

  /**
   * Turns on filling polygons
   */
  void handleModelFill();

  /**
   * Turns off filling polygons(wireframe)
   */
  void handleModelWireframe();

  /**
   * Light positin getter
   * @return light position
   */
  const glm::vec3 &getLightPos() const;

  /**
   * Light position setter
   * @param lightPos position of light to set
   */
  void setLightPos(const glm::vec3 &lightPos);

  /**
   * Handles clicking on window and object selection
   * @param x x position of click
   * @param y y position of click
   * @param objects models to choose from
   */
  void handleSelectObject(int x, int y, std::vector<GraphicsModel *> &objects);

  /**
   * Clears all selected objects
   * @param objects
   */
  void clearSelectedObjects(std::vector<GraphicsModel *> &objects);

};
}
#endif //PGR_PROJECT_GRAPHICSCORE_H
