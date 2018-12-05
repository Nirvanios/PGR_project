//
// Created by kuro on 2.12.18.
//

#ifndef PGR_PROJECT_GRAPHICSCORE_H
#define PGR_PROJECT_GRAPHICSCORE_H

#include "../../third_party/Camera.h"
#include <objects/GraphicsModel.h>
#include "Shader.h"

namespace PGRgraphics {

class GraphicsCore {
private:

    // GL identifiers
    GLuint normalMatGLUniform;
    GLint projGLUniform;
    GLint modelViewGLUniform;
    GLint lightPosUniform;
    GLuint inputColorUniform;

    std::string programName;
    SDL_Window *mainWindow;
    SDL_GLContext mainContext;
    int width = 1200, height = 700;
    Camera camera;
    Shader shader;

    const GLuint positionAttributeIndex = 0, colorAttributeIndex = 1, normalAttributeIndex = 2;

    GLuint vao[1];
    std::vector<GLuint> vbo;
    std::vector<glm::vec3> vboC;
    std::vector<GLuint> ebo;
    std::vector<GLuint> nbo;

    glm::vec3 lightPos = glm::vec3(0, -2, 0);
public:
    virtual ~GraphicsCore();

private:
    void cleanup();

    void checkSDLError(int);

    bool setOpenGLAttributes();

    void deleteBuffers(std::vector<GLuint> &);

    glm::vec3 getRandColor();

public:
    GraphicsCore();

public:
    bool init();

    bool setupBufferObjects(std::vector<GraphicsModel *> &);

    void render(std::vector<GraphicsModel *> &);

    void handleResize();

    void handleCameraMove(SDL_Keycode);

    void handleMouseMove(float, float);
  void handleMouseWheel(float yOffset);

    void mainLoop();

    const glm::vec3 &getLightPos() const;

    void setLightPos(const glm::vec3 &lightPos);

};
}
#endif //PGR_PROJECT_GRAPHICSCORE_H
