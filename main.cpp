#include <iostream>

#define _USE_MATH_DEFINES
#include <cmath>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;

constexpr int OPENGL_MAJOR_VERSION = 2;
constexpr int OPENGL_MINOR_VERSION = 1;

constexpr SDL_GLprofile OPENGL_PROFILE = SDL_GLprofile::SDL_GL_CONTEXT_PROFILE_CORE;

/*
 * http:*nehe.gamedev.net/article/replacement_for_gluperspective/21002/
 *
 * Replaces gluPerspective. Sets the frustum to perspective mode.
 * fovY     - Field of vision in degrees in the y direction
 * aspect   - Aspect ratio of the viewport
 * zNear    - The near clipping distance
 * zFar     - The far clipping distance
 */

void perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar) {

    GLdouble fW, fH;

    fH = tan(fovY / 360 * M_PI) * zNear;
    fW = fH * aspect;

    glFrustum(-fW, fW, -fH, fH, zNear, zFar);

}

void Display_InitGL() {

    /* Enable smooth shading */
    glShadeModel( GL_SMOOTH);

    /* Set the background red */
    glClearColor(1.0f, 0.0f, 0.0f, 0.0f);

    /* Depth buffer setup */
    glClearDepth(1.0f);

    /* Enables Depth Testing */
    glEnable( GL_DEPTH_TEST);

    /* The Type Of Depth Test To Do */
    glDepthFunc( GL_LEQUAL);

    /* Really Nice Perspective Calculations */
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

/* function to reset our viewport after a window resize */
int Display_SetViewport(int width, int height) {

    /* Height / width ration */
    GLfloat ratio;

    /* Protect against a divide by zero */
    if (height == 0) {
        height = 1;
    }

    ratio = (GLfloat) width / (GLfloat) height;

    /* Setup our viewport. */
    glViewport(0, 0, (GLsizei) width, (GLsizei) height);

    /* change to the projection matrix and set our viewing volume. */
    glMatrixMode( GL_PROJECTION);
    glLoadIdentity();

    /* Set our perspective */
    perspectiveGL(45.0f, ratio, 0.1f, 100.0f);

    /* Make sure we're chaning the model view and not the projection */
    glMatrixMode( GL_MODELVIEW);

    /* Reset The View */
    glLoadIdentity();

    return 1;
}

void Display_Render(SDL_Window* displayWindow) {

    /* Clear The Screen And The Depth Buffer */
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor4f(0, 0, 0, 1.0);

    /* Move Left 1.5 Units And Into The Screen 6.0 */
    glLoadIdentity();
    glTranslatef(-1.5f, 0.0f, -6.0f);

    glBegin( GL_TRIANGLES); /* Drawing Using Triangles */
    glVertex3f(0.0f, 1.0f, 0.0f); /* Top */
    glVertex3f(-1.0f, -1.0f, 0.0f); /* Bottom Left */
    glVertex3f(1.0f, -1.0f, 0.0f); /* Bottom Right */
    glEnd(); /* Finished Drawing The Triangle */

    /* Move Right 3 Units */
    glTranslatef(3.0f, 0.0f, 0.0f);

    glBegin( GL_QUADS); /* Draw A Quad */
    glVertex3f(-1.0f, 1.0f, 0.0f); /* Top Left */
    glVertex3f(1.0f, 1.0f, 0.0f); /* Top Right */
    glVertex3f(1.0f, -1.0f, 0.0f); /* Bottom Right */
    glVertex3f(-1.0f, -1.0f, 0.0f); /* Bottom Left */
    glEnd(); /* Done Drawing The Quad */

    SDL_GL_SwapWindow(displayWindow);

}

int main(int argc, char *argv[]) {

    if (SDL_Init( SDL_INIT_VIDEO) < 0) {
        std::cerr << "There was an error initing SDL2: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, OPENGL_PROFILE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, OPENGL_MAJOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, OPENGL_MINOR_VERSION);

    SDL_Window* displayWindow = SDL_CreateWindow("Very basic SDL2 OpenGL application", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

    if (displayWindow == nullptr) {
        std::cerr << "There was an error creating the window: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);

    if (context == nullptr) {
        std::cerr << "There was an error creating OpenGL context: " << SDL_GetError() << std::endl;
        return 1;
    }

    const unsigned char *version = glGetString(GL_VERSION);
    if (version == nullptr) {
        std::cerr << "There was an error with OpenGL configuration:" << std::endl;
        return 1;
    }

    SDL_GL_MakeCurrent(displayWindow, context);

    Display_InitGL();

    Display_SetViewport(SCREEN_WIDTH, SCREEN_HEIGHT);

    Display_Render(displayWindow);

    SDL_Delay(5000);

    SDL_GL_DeleteContext(context);

    SDL_DestroyWindow(displayWindow);

    SDL_Quit();

    return 0;
}