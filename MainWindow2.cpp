// Headerphile.com OpenGL Tutorial part 2
// A simple example involving VBOs and a VAO to draw a simple square
// Source code is an adaption / simplicication of : https://www.opengl.org/wiki/Tutorial2:_VAOs,_VBOs,_Vertex_and_Fragment_Shaders_(C_/_SDL)

// Compile :
// 	clang++ main.cpp -lGL -lGLEW -lSDL2 -std=c++11 -o Test
// or
// 	g++ main.cpp -lGL -lGLEW -lSDL2 -std=c++11 -o Test
//
#include <iostream>
#include <string>

#include "shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GL3_PROTOTYPES 1
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SimpleGraphicsModel.h>
#include <vector>

#define PROGRAM_NAME "Tutorial2"

std::string programName = "Headerphile SDL2 - OpenGL thing";

// Our SDL_Window ( just like with SDL2 wihout OpenGL)
SDL_Window *mainWindow;

// Our opengl context handle
SDL_GLContext mainContext;

// Our object has 4 points
const uint32_t points = 4;

// Each point has three values ( x, y, z)
const uint32_t floatsPerPoint = 3;

// Each color has 4 values ( red, green, blue, alpha )
const uint32_t floatsPerColor = 4;

// This is the object we'll draw ( a simple square
float diamond[] =
        { -1.5,  1.5,  1.5 , // Top left
         1.5,  1.5,  1.5 , // Top right
          1.5, -1.5, 1.5 , // Bottom right
         -1.5, -1.5, 1.5 } // Bottom left
;

float diamond2[] =
        { 0.5,  0.5,  0.5 , // Top left
          0.5,  0.5,  -0.5 , // Top right
          0.5, -0.5,  -0.5 , // Bottom right
          0.5, -0.5, 0.5 } // Bottom left
;

// This is the object we'll draw ( a simple square
float colors[] = {
         0.0, 1.0, 0.0, 1.0, // Top left
        1.0, 1.0, 0.0, 1.0,   // Top right
         1.0, 0.0, 0.0, 1.0,   // Bottom right
         0.0, 0.0, 1.0, 1.0  }; // Bottom left;

unsigned char indicies[] = {
        0, 1, 2,
        0, 2, 3
};

// Create variables for storing the ID of our VAO and VBO
GLuint /*vbo[2],*/ vao[1]/*, ebo*/;
GLuint mvpUniform;

std::vector<GLuint> *vbo = new std::vector<GLuint>();
std::vector<GLuint> *ebo = new std::vector<GLuint>();


float rx = 0.0f, ry = 0.0f, pz = -70.0f;

float wheel = 1.0f;
float z = 0.0f;

// The positons of the position and color data within the VAO
const uint32_t positionAttributeIndex = 0, colorAttributeIndex = 1;

// Our wrapper to simplify the shader code
Shader shader;

bool SetOpenGLAttributes();
void PrintSDL_GL_Attributes();
void CheckSDLError(int line);

Uint32  Render(std::vector<SimpleGraphicsModel> *objects)
{
    z += 0.05f;
    // First, render a square without any colors ( all vertexes will be black )
    // ===================
    // Make our background grey
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glm::mat4 translate = glm::mat4(1,0,0,0,
                                    0,1,0,2,
                                    0,0,1,0,
                                    0,0,0,1);

// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float) 512 / (float)512, 0.1f, 100.0f);

// Or, for an ortho camera :
//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

// Camera matrix
    glm::mat4 View = glm::lookAt(
            glm::vec3(0,0,10), // Camera is at (4,3,3), in World Space
            glm::vec3(0,0,0), // and looks at the origin
            glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

// Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model = glm::mat4(1.0f);
    //Model = glm::translate(Model, glm::vec3(0,1,0));
// Our ModelViewProjection : multiplication of our 3 matrices
    glm::mat4 mvp = Projection * View * Model; // Remember, matrix multiplication is the other way around

    GLuint MatrixID = shader.getUniformLocation("mvp");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);


    // Invoke glDrawArrays telling that our data is a line loop and we want to draw 2-4 vertexes
    int i = 0;
    for(auto item : *objects) {
        glBindBuffer(GL_ARRAY_BUFFER ,vbo->at(i));
        glEnableVertexAttribArray(positionAttributeIndex);
        glVertexAttribPointer(positionAttributeIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo->at(i));
        // Specify that our coordinate data is going into attribute index 0, and contains three floats per vertex

        glDrawElements(GL_TRIANGLES, item.getIndiciesSize(), GL_UNSIGNED_BYTE, NULL);
        GLuint MatrixID = shader.getUniformLocation("mvp");
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
        //glDisableVertexAttribArray(positionAttributeIndex);
        i++;
    }

    // Swap our buffers to make our changes visible
    SDL_GL_SwapWindow(mainWindow);

    /*std::cout << "Press ENTER to render next frame\n";
    std::cin.ignore();

    // Second, enable the colors and draw a solid square
    // ===================
    // Enable our attribute within the current VAO
    glEnableVertexAttribArray(colorAttributeIndex);

    // Make our background black
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    // Invoke glDrawArrays telling that our data is a line loop and we want to draw 2-4 vertexes
    glDrawElements(GL_TRIANGLES, sizeof(indicies)/sizeof(*indicies), GL_UNSIGNED_BYTE, NULL);


    // Swap our buffers to make our changes visible
    SDL_GL_SwapWindow(mainWindow);

    std::cout << "Press ENTER to render next frame\n";
    std::cin.ignore();
*/
}
bool SetupBufferObjects(std::vector<SimpleGraphicsModel> *objects)
{

    GLuint tempVBO;
    mvpUniform = shader.getUniformLocation("mvp");
    // Generate and assign two Vertex Buffer Objects to our handle
/*
    glGenBuffers(1, &tempVBO);

    vbo->push_back(tempVBO);
*/
    // Generate and assign a Vertex Array Object to our handle
    glGenVertexArrays(1, vao);

    // Bind our Vertex Array Object as the current used object
    glBindVertexArray(vao[0]);

    // Positions
    // ===================
    // Bind our first VBO as being the active buffer and storing vertex attributes (coordinates)
    for(auto item : *objects) {
        glGenBuffers(1, &tempVBO);

        glBindBuffer(GL_ARRAY_BUFFER, tempVBO);
        vbo->push_back(tempVBO);


        // Copy the vertex data from diamond to our buffer
        glBufferData(GL_ARRAY_BUFFER, (item.getVerticesSize() * sizeof(float)), item.getVertices(),
                     GL_STATIC_DRAW);

        // Specify that our coordinate data is going into attribute index 0, and contains three floats per vertex
        //glVertexAttribPointer(positionAttributeIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);

        // Enable our attribute within the current VAO
        //glEnableVertexAttribArray(positionAttributeIndex);
    }

    // Colors
    // =======================
    glGenBuffers(1, &tempVBO);
    glBindBuffer(GL_ARRAY_BUFFER, tempVBO);
    vbo->push_back(tempVBO);

    // Copy the vertex data from diamond to our buffer
    glBufferData(GL_ARRAY_BUFFER, ( points * floatsPerColor) * sizeof(GLfloat), colors, GL_STATIC_DRAW);

    // Specify that our coordinate data is going into attribute index 0, and contains three floats per vertex
    glVertexAttribPointer(colorAttributeIndex, 4, GL_FLOAT, GL_FALSE, 0, 0);

    // Note : We didn't enable the colors here!
    for(auto item : *objects) {
        GLuint tempEBO;
        glGenBuffers(1, &tempEBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tempEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, item.getIndiciesSize(), item.getIndices(), GL_STATIC_DRAW);
        ebo->push_back(tempEBO);
    }

    // Set up shader ( will be covered in the next part )
    // ===================
    if (!shader.Init())
        return false;

    shader.UseProgram();

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return true;
}
bool Init()
{
    // Initialize SDL's Video subsystem
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
    {
        std::cout << "Failed to init SDL\n";
        return false;
    }

    // Create our window centered at 512x512 resolution
    mainWindow = SDL_CreateWindow(programName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  512, 512, SDL_WINDOW_OPENGL);

    // Check that everything worked out okay
    if (!mainWindow )
    {
        std::cout << "Unable to create window\n"<< std::endl;;
        CheckSDLError(__LINE__);
        return false;
    }

    SetOpenGLAttributes();

    // Create our opengl context and attach it to our window
    mainContext = SDL_GL_CreateContext(mainWindow );

    // This makes our buffer swap syncronized with the monitor's vertical refresh
    SDL_GL_SetSwapInterval(1);

    // Init GLEW
    glewExperimental = GL_TRUE;
    glewInit();

    return true;
}

bool SetOpenGLAttributes()
{
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

void Cleanup()
{
    // Cleanup all the things we bound and allocated
    shader.CleanUp();

    glDisableVertexAttribArray(0);
    //glDeleteBuffers(1, vbo);
    glDeleteVertexArrays(1, vao);

    // Delete our OpengL context
    SDL_GL_DeleteContext(mainContext);

    // Destroy our window
    SDL_DestroyWindow(mainWindow );

    // Shutdown SDL 2
    SDL_Quit();
}

int main(int argc, char *argv[]) {


    if (!Init())
        return -1;

    // Clear our buffer with a grey background
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    SDL_GL_SwapWindow(mainWindow);

    std::cout << "Seting up VBO + VAO..." << std::endl;
    const glm::vec3 aaa = glm::vec3(0.0f);
    SimpleGraphicsModel object = SimpleGraphicsModel(aaa, diamond, 12, indicies, 6);
    std::vector<SimpleGraphicsModel> *objects = new std::vector<SimpleGraphicsModel>();
    objects->push_back(object);
    object = SimpleGraphicsModel(aaa, diamond2, 12, indicies, 6);
    objects->push_back(object);


    if (!SetupBufferObjects(objects))
        return -1;

    std::cout << "Rendering..." << std::endl;
    //Render(0, nullptr);
    //SDL_TimerID my_timer_id = SDL_AddTimer(5000, Render, NULL);
    //std::cout << my_timer_id << std::endl;
    while(true){
        Render(objects);
        SDL_Delay(16);
    }



    std::cout << "Rendering done!\n";
    std::cin.ignore();

    Cleanup();

    return 0;
}

void CheckSDLError(int line = -1)
{
    std::string error = SDL_GetError();

    if (error != "")
    {
        std::cout << "SLD Error : " << error << std::endl;

        if (line != -1)
            std::cout << "\nLine : " << line << std::endl;

        SDL_ClearError();
    }
}

void PrintSDL_GL_Attributes()
{
    int value = 0;
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &value);
    std::cout << "SDL_GL_CONTEXT_MAJOR_VERSION : " << value << std::endl;

    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &value);
    std::cout << "SDL_GL_CONTEXT_MINOR_VERSION: " << value << std::endl;
}