//
// Created by Petr Flajsingr on 2018-12-02.
//

#ifndef PGR_PROJECT_SHADOWCALC_H
#define PGR_PROJECT_SHADOWCALC_H

//#include <gl/glew.h>
#include <glm/glm.hpp>
#include "../shader.h"

class ShadowCalc {
 private:
  unsigned int depthMapFBO;

  unsigned int width, height;
  unsigned int depthMap;

  GLuint lightSpaceMatrixLocation;


  float near_plane = 1.0f, far_plane = 7.5f;

  Shader shader;
 protected:
 public:
  ShadowCalc(unsigned int width, unsigned int height);

 bool calculateShadows();

 bool renderWithShadows();

 bool configureShaderAndMatrices();
};

#endif //PGR_PROJECT_SHADOWCALC_H
