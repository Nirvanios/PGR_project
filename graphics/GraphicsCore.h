//
// Created by kuro on 2.12.18.
//

#ifndef PGR_PROJECT_GRAPHICSCORE_H
#define PGR_PROJECT_GRAPHICSCORE_H


#include <camera/Camera.h>
#include "../graphicObjects/SimpleGraphicsModel.h"
#include "Shader.h"

class GraphicsCore {
private:
    std::string programName;
    SDL_Window *mainWindow;
    SDL_GLContext mainContext;
    int width = 512, height = 512;
    Camera camera;
    Shader shader;

    const GLuint positionAttributeIndex = 0, colorAttributeIndex = 1;

    GLuint vao[1];
    std::vector<GLuint> *vbo = new std::vector<GLuint>();
    std::vector<GLuint> *vboC = new std::vector<GLuint>();
    std::vector<GLuint> *ebo = new std::vector<GLuint>();

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
    void deleteBuffers( std::vector<GLuint> *);
public:
    bool init();
    bool setupBufferObjects(std::vector<SimpleGraphicsModel*>*);
    void render(std::vector<SimpleGraphicsModel*>*);
    void handleResize();
    void handleCameraMove(SDL_Keycode);
    void handleMouseMove(float, float, GLboolean);
    void mainLoop();
    void cleanup();


};


#endif //PGR_PROJECT_GRAPHICSCORE_H
