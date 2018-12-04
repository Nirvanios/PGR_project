//
// Created by kuro on 2.12.18.
//


#include <SDL.h>
#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include "SimpleGraphicsModel.h"
#include "GraphicsCore.h"
#include "Shader.h"

bool GraphicsCore::init() {
    // Initialize SDL's Video subsystem
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        std::cout << "Failed to init SDL\n";
        return false;
    }

    // Create our window centered at 512x512 resolution
    mainWindow = SDL_CreateWindow(programName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    // Check that everything worked out okay
    if (!mainWindow) {
        std::cout << "Unable to create window\n" << std::endl;
        checkSDLError(__LINE__);
        return false;
    }

    setOpenGLAttributes();

    // Create our opengl context and attach it to our window
    mainContext = SDL_GL_CreateContext(mainWindow);

    SDL_GL_SetSwapInterval(1);

    // Init GLEW
    glewExperimental = GL_TRUE;
    glewInit();

    camera.Position = glm::vec3(0, 0, 5);

    // Clear our buffer with a grey background
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    return true;
}

bool GraphicsCore::setOpenGLAttributes() {
    // Set our OpenGL version.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    return true;
}


void GraphicsCore::checkSDLError(int line = -1) {
    std::string error = SDL_GetError();

    if (error != "") {
        std::cerr << "SLD Error : " << error << std::endl;

        if (line != -1)
            std::cerr << "\nLine : " << line << std::endl;

        SDL_ClearError();
    }
}

bool GraphicsCore::setupBufferObjects(std::vector<GraphicsModel*>& objects) {

    GLuint tempVBO;

    // Generate and assign a Vertex Array Object to our handle
    glGenVertexArrays(1, vao);

    // Bind our Vertex Array Object as the current used object
    glBindVertexArray(vao[0]);

    // Positions
    // ===================
    // Bind our first VBO as being the active buffer and storing vertex attributes (coordinates)
    for (auto item : objects) {
        glGenBuffers(1, &tempVBO);

        glBindBuffer(GL_ARRAY_BUFFER, tempVBO);
        vbo.push_back(tempVBO);


        // Copy the vertex data from diamond to our buffer
        glBufferData(GL_ARRAY_BUFFER, (item->getVertices().size() * 3 * sizeof(float)), item->getVertices().data(),
                     GL_DYNAMIC_DRAW);

    }

    glGenBuffers(1, &tempVBO);
    glBindBuffer(GL_ARRAY_BUFFER, tempVBO);
    vbo.push_back(tempVBO);
    // Copy the vertex data from diamond to our buffer
    glBufferData(GL_ARRAY_BUFFER, sceneFloor.size() * sizeof(unsigned int), sceneFloor.data(),
                 GL_STATIC_DRAW);

    // Colors
    // =======================
    glGenBuffers(1, &tempVBO);
    glBindBuffer(GL_ARRAY_BUFFER, tempVBO);
    vboC.push_back(tempVBO);

    // Copy the vertex data from diamond to our buffer
    glBufferData(GL_ARRAY_BUFFER, floorColor.size() * sizeof(float), floorColor.data(), GL_STATIC_DRAW);

    // Specify that our coordinate data is going into attribute index 0, and contains three floats per vertex
    //glVertexAttribPointer(colorAttributeIndex, 4, GL_FLOAT, GL_FALSE, 0, 0);

    GLuint tempEBO;
    for (auto item : objects) {
        glGenBuffers(1, &tempEBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tempEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, item->getVertexIndices().size() * sizeof(int), item->getVertexIndices().data(), GL_STATIC_DRAW);
        ebo.push_back(tempEBO);
    }

    glGenBuffers(1, &tempEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tempEBO);
    //glVertexAttribPointer(colorAttributeIndex, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, floorIndicies.size() * sizeof(float), floorIndicies.data(), GL_STATIC_DRAW);
    ebo.push_back(tempEBO);

    GLuint tempNBO;
    for (auto item : objects) {
        glGenBuffers(1, &tempNBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tempNBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, item->getNormals().size() * sizeof(float), item->getNormals().data(), GL_STATIC_DRAW);
        nbo.push_back(tempNBO);
    }

    // Set up shader ( will be covered in the next part )
    // ===================
    if (!shader.Init())
        return false;

    shader.UseProgram();

    modelViewGLUniform = shader.getUniformLocation("modelview");
    projGLUniform = shader.getUniformLocation("projection");
    normalMatGLUniform = shader.getUniformLocation("normalMat");
    translateGLUniform = shader.getUniformLocation("translate");


    return true;
}

void GraphicsCore::render(std::vector<GraphicsModel*>& objects) {
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
    glUniform1i(shader.getUniformLocation("mode"), 4);

// Our ModelViewProjection : multiplication of our 3 matrices
    glm::mat4 modelView = Model * camera.GetViewMatrix(); // Remember, matrix multiplication is the other way around

    glUniformMatrix4fv(modelViewGLUniform, 1, GL_FALSE, glm::value_ptr(modelView));
    glUniformMatrix4fv(projGLUniform, 1, GL_FALSE, glm::value_ptr(Projection));
    auto normalMV = glm::transpose(glm::inverse(modelView));
    glUniformMatrix4fv(normalMatGLUniform, 1, GL_FALSE, glm::value_ptr(normalMV));



    glDisableVertexAttribArray(colorAttributeIndex);

    // Invoke glDrawArrays telling that our data is a line loop and we want to draw 2-4 vertexes
    int i = 0;
    for (auto item : objects) {
        /*if (item->isLine()) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }*/

        glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
        glBufferSubData(GL_ARRAY_BUFFER, 0, (item->getVertices().size()* 3 * sizeof(float)), item->getVertices().data());
        glEnableVertexAttribArray(positionAttributeIndex);
        glVertexAttribPointer(positionAttributeIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, nbo[i]);
        glEnableVertexAttribArray(normalAttributeIndex);
        glVertexAttribPointer(normalAttributeIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i]);
        // Specify that our coordinate data is going into attribute index 0, and contains three floats per vertex

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
        if (dynamic_cast<SimpleGraphicsModel*>(item) != nullptr) {
            glUniformMatrix4fv(translateGLUniform, 1, GL_FALSE, glm::value_ptr(dynamic_cast<SimpleGraphicsModel*>(item)->getTranslationMatrix()));
        }
#pragma clang diagnostic pop
        glDrawElements(GL_TRIANGLES, item->getVertexIndices().size() * sizeof(int), GL_UNSIGNED_INT, NULL);
        //glDisableVertexAttribArray(positionAttributeIndex);
        i++;
/*
        if (item->isLine()) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }*/
    }

    glBindBuffer(GL_ARRAY_BUFFER, vbo.back());
    glEnableVertexAttribArray(positionAttributeIndex);
    glVertexAttribPointer(positionAttributeIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, vboC.back());
    glEnableVertexAttribArray(colorAttributeIndex);
    glVertexAttribPointer(colorAttributeIndex, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo.back());
    glUniformMatrix4fv(translateGLUniform, 1, GL_FALSE, glm::value_ptr(Model));
    glDrawElements(GL_TRIANGLES, sizeof(floorIndicies.data()), GL_UNSIGNED_BYTE, NULL);


    // Swap our buffers to make our changes visible
    SDL_GL_SwapWindow(mainWindow);

}

void mainLoop(){

}

void GraphicsCore::cleanup() {
    // Cleanup all the things we bound and allocated
    shader.CleanUp();

    glDisableVertexAttribArray(0);

    deleteBuffers(vbo);
    deleteBuffers(vboC);
    deleteBuffers(ebo);

    glDeleteVertexArrays(1, vao);

    // Delete our OpengL context
    SDL_GL_DeleteContext(mainContext);

    // Destroy our window
    SDL_DestroyWindow(mainWindow);

    // Shutdown SDL 2
    SDL_Quit();
}

void GraphicsCore::deleteBuffers(std::vector<GLuint> &buff){
    int i = 0;
    for(auto item : buff) {
        glDeleteBuffers(i, &item);
        i++;
    }
}

void GraphicsCore::handleResize() {
    SDL_GetWindowSize(mainWindow, &width, &height);
    glViewport(0, 0, width, height);
}

void GraphicsCore::handleCameraMove(SDL_Keycode key) {
    switch(key) {
        case SDLK_w:
            camera.ProcessKeyboard(FORWARD, 0.05);
            break;
        case SDLK_s:
            camera.ProcessKeyboard(BACKWARD, 0.05);
            break;
        case SDLK_a:
            camera.ProcessKeyboard(LEFT, 0.05);
            break;
        case SDLK_d:
            camera.ProcessKeyboard(RIGHT, 0.05);
            break;
    }

}

void GraphicsCore::handleMouseMove(float xoffset, float yoffset, GLboolean constrainPitch) {
    camera.ProcessMouseMovement(xoffset, yoffset, constrainPitch);
}
