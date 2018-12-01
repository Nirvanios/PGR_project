//
// Created by kuro on 1.12.18.
//

#include <iostream>
#include <string>
#include <stdarg.h>

#define _USE_MATH_DEFINES
#include <cmath>

#include <GL/glew.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_opengl.h>
#include <vector>

using namespace std;

const int WIDTH = 640;
const int HEIGHT = 480;

SDL_Window* window;

GLuint vertexShader, fragmentShader, pointsVBO, shaderProgram, positionAttrib;


const char *vertexShaderSource = "#version 120 \n attribute vec2 position; void main() { gl_Position = vec4(position,0,1); }";
const char *fragmentShaderSource = "#version 120 \n  vec4 fragColor; void main() { fragColor = vec4(1); }";


const float points[][2] = {
        {0,0.8}, {0.6,0.6}, {0.8, 0}, {0.6, -0.6},
        {0, -0.8}, {-0.6, -0.6}, {-0.8, 0}, {-0.6, 0.6}
};

void onInit();

void onWindowRedraw();

void onWindowResize(unsigned width, unsigned height){
    glViewport(0, 0, width, height);
}


SDL_GLContext  init(unsigned color, unsigned depth, unsigned stencil){
    if(SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, color) < 0) cout << "Err1" << endl; //throw SDL_Exception();
    if(SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, depth) < 0)cout << "Err2" << endl; //throw SDL_Exception();
    if(SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, stencil) < 0)cout << "Err3" << endl; //throw SDL_Exception();
    if(SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) < 0)cout << "Err4" << endl; //throw SDL_Exception();

    window = SDL_CreateWindow("Elastic Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

    SDL_GLContext context = SDL_GL_CreateContext(window);

#ifndef USE_GLEE
    // Init extensions
    GLenum error = glewInit();
    if(error != GLEW_OK)
        throw std::runtime_error(std::string("GLEW : Init failed : ") + (const char*)glewGetErrorString(error));
#endif//USE_GLEE
    // Call init code
    onInit();

    onWindowResize(WIDTH, HEIGHT);

    return context;
}

GLuint linkShader(vector<GLuint> shaders) {
    // Create program object
    GLuint program = glCreateProgram();
    if(program == 0){
        cout << "Create program Error." << endl;
    } //throw GL_Exception("glCreateProgram failed");

    // Attach arguments
    for(auto &shader : shaders)
    {
        glAttachShader(program, shader);
    }

    // Link program and check for errors
    glLinkProgram(program);
    //std::cout << glGetProgramInfoLog(program);

    int linkStatus;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
    if(linkStatus == GL_FALSE) {
        cout << "Shader link error." << endl;
        throw std::runtime_error("shader linking failed");
    }

    return program;
}

GLuint compileShader(GLenum type, char* source);

void onInit() {
    // Compile shaders
    vertexShader = compileShader(GL_VERTEX_SHADER, (char*) vertexShaderSource);
    GLint isCompiled = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &errorLog[0]);

        for (auto ch : errorLog) {
            std::cerr << ch;
        }
        std::cerr << std::endl;
        // Provide the infolog in whatever manor you deem best.
        // Exit with failure.
        glDeleteShader(vertexShader); // Don't leak the shader.
        return;
    }


    fragmentShader = compileShader(GL_FRAGMENT_SHADER, (char*) fragmentShaderSource);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &errorLog[0]);


        for (auto ch : errorLog) {
            std::cerr << ch;
        }
        std::cerr << std::endl;
        // Provide the infolog in whatever manor you deem best.
        // Exit with failure.
        glDeleteShader(fragmentShader); // Don't leak the shader.
        return;
    }

    // Link shaders
    vector<GLuint> *shaders = new vector<GLuint>(vertexShader, fragmentShader);
    shaderProgram = linkShader(*shaders);

    // Get location of the "position" attribute
    positionAttrib = glGetAttribLocation(shaderProgram, "position");

    // Copy points to graphics card
    glGenBuffers(1, &pointsVBO);
    glBindBuffer(GL_ARRAY_BUFFER, pointsVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
}



void mainLoop(){
    bool active = true;

    while (true){
        SDL_Event event;

        if(SDL_WaitEvent(&event) == 0); //throw SDL_Exception();

        bool redraw = false;

        do{
            switch(event.type){
                case SDL_WINDOWEVENT:
                    switch(event.window.event) {
                        case SDL_WINDOWEVENT_SHOWN:
                            active = true;
                            break;
                        case SDL_WINDOWEVENT_HIDDEN:
                            active = false;
                            break;
                        case SDL_WINDOWEVENT_RESIZED:
                            onWindowResize(WIDTH, HEIGHT);
                            break;
                        case SDL_WINDOWEVENT_EXPOSED:
                            redraw = true;
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_QUIT:
                    return;
                default:
                    break;
            }
        }while(SDL_PollEvent(&event) == 1);

        if(active && redraw) onWindowRedraw();
    }
}

void onWindowRedraw() {
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);

    glEnableVertexAttribArray(positionAttrib);

    glBindBuffer(GL_ARRAY_BUFFER, pointsVBO);
    glVertexAttribPointer(positionAttrib, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(points)/ sizeof(*points));

    SDL_GL_SwapWindow(window);

}

GLuint compileShader(GLenum type, char *source) {
    GLuint shader = glCreateShader(type);
    if(shader == 0){
        cout << "Create shader error." << endl;
        //throw GL_Exception("glCreateShader");
    }
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    int compilationStatus;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compilationStatus);
//    if(compilationStatus == GL_FALSE) throw runtime_error("Shader compilation error.");

    return shader;
}

int main(int argc, char* args[]){

    if( SDL_Init(SDL_INIT_VIDEO) < 0){
        cout << "Could not initialize SDL. " << SDL_GetError() << endl;
    }
    else {
        SDL_GLContext context = init(24, 0, 0);

        atexit(SDL_Quit);

        mainLoop();

        SDL_GL_DeleteContext(context);
    }



    return 0;
}
