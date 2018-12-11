//
// Created by Petr Flajsingr on 2018-12-04.
//

#ifndef PGR_PROJECT_SIMPLEGRAPHICSMODEL_H
#define PGR_PROJECT_SIMPLEGRAPHICSMODEL_H

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <StdoutLogger.h>
#include "GraphicsModel.h"
#include <algorithm>

namespace PGRgraphics {

/**
 * Basic model whose translation is gaine via getTranslationMatrix() method.
 *
 * @author Petr Flajšingr, Igor Frank
 */
class SimpleGraphicsModel : public GraphicsModel {
 private:
  const glm::mat4 model = glm::mat4(1.f);

  static SimpleGraphicsModel *LoadFromFile(std::string path);

 protected:
  glm::vec3 position;
 public:
  static PGRgraphics::SimpleGraphicsModel *LoadFromOBJ(std::string path);

  static PGRgraphics::SimpleGraphicsModel *LoadFromOBJ(std::string path, glm::vec3 color);

  const glm::vec3 &getPosition() const;

  void setPosition(const glm::vec3 &position);

  glm::mat4 getTranslationMatrix();
};
}
#endif //PGR_PROJECT_SIMPLEGRAPHICSMODEL_H
