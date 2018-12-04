//
// Created by kuro on 2.12.18.
//

#ifndef PGR_PROJECT_GRAPHICSCORE_H
#define PGR_PROJECT_GRAPHICSCORE_H


#include <camera/Camera.h>
#include <objects/GraphicsModel.h>
#include "Shader.h"

class GraphicsCore {
private:

  // GL identifiers
  GLuint projGLUniform, modelViewGLUniform, normalMatGLUniform, translateGLUniform, modeGLUniform;

    std::string programName;
    SDL_Window *mainWindow;
    SDL_GLContext mainContext;
    int width = 1200, height = 700;
    Camera camera;
    Shader shader;

    const GLuint positionAttributeIndex = 0, colorAttributeIndex = 1;

    GLuint vao[1];
    std::vector<GLuint> vbo;
    std::vector<GLuint> vboC;
    std::vector<GLuint> ebo;

    const std::vector<float> sceneFloor={
            -100, -10, 100,
            -100, -10, -100,
            100, -10, 100,
            100, -10, -100
    };

    const std::vector<unsigned char> floorIndicies={
            0, 1, 2,
            1, 2, 3
    };

    const std::vector<float> floorColor={
            0.0, 1.0, 0.0, 1.0,
            0.0, 1.0, 0.0, 1.0,
            0.0, 1.0, 0.0, 1.0,
            0.0, 1.0, 0.0, 1.0
    };


    void checkSDLError(int);
    bool setOpenGLAttributes();
    void deleteBuffers(std::vector<GLuint>&);
public:
    bool init();
    bool setupBufferObjects(std::vector<GraphicsModel*>&);
    void render(std::vector<GraphicsModel*>&);
    void handleResize();
    void handleCameraMove(SDL_Keycode);
    void handleMouseMove(float, float, GLboolean);
    void mainLoop();
    void cleanup();


};


#endif //PGR_PROJECT_GRAPHICSCORE_H
