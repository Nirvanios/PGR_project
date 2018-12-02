//
// Created by Petr Flajsingr on 2018-12-02.
//

#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ShadowCalc.h"


ShadowCalc::ShadowCalc(unsigned int width, unsigned int height) : width(width), height(height) {
  glGenFramebuffers(1, &depthMapFBO);

  glGenTextures(1, &depthMap);
  glBindTexture(GL_TEXTURE_2D, depthMap);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
               width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


  glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
  glDrawBuffer(GL_NONE);
  glReadBuffer(GL_NONE);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  shader.LoadFragmentShader("../shaders/shadow_fragment.glsl");
  shader.LoadVertexShader("../shaders/shadow_vertex.glsl");

  lightSpaceMatrixLocation = shader.getUniformLocation("lightSpaceMatrix");
}
bool ShadowCalc::calculateShadows() {
  // 1. first render to depth map
  glViewport(0, 0, width, height);
  glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
  glClear(GL_DEPTH_BUFFER_BIT);
  configureShaderAndMatrices();
  //renderScene();
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
bool ShadowCalc::renderWithShadows() {
  // 2. then render scene as normal with shadow mapping (using depth map)
  glViewport(0, 0, width, height);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  configureShaderAndMatrices();
  glBindTexture(GL_TEXTURE_2D, depthMap);
}
bool ShadowCalc::configureShaderAndMatrices() {
  glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);

  glm::mat4 lightView = glm::lookAt(glm::vec3(-2.0f, 4.0f, -1.0f),
                                    glm::vec3( 0.0f, 0.0f,  0.0f),
                                    glm::vec3( 0.0f, 1.0f,  0.0f));

  glm::mat4 lightSpaceMatrix = lightProjection * lightView;

  shader.UseProgram();
  glUniformMatrix4fv(lightSpaceMatrixLocation, 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));

  glViewport(0, 0, width, height);
  glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
  glClear(GL_DEPTH_BUFFER_BIT);
  //RenderScene(shader);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


