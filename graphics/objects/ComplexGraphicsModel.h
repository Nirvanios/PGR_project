//
// Created by Petr Flajsingr on 2018-12-04.
//

#ifndef PGR_PROJECT_COMPLEXGRAPHICSMODEL_H
#define PGR_PROJECT_COMPLEXGRAPHICSMODEL_H

#include <StdoutLogger.h>
#include "GraphicsModel.h"
#include <algorithm>

namespace PGRgraphics {

/**
 * Model consisting of possibly changing vertex locations and triangle count.
 * @author Petr Flajšingr, Igor Frank
 */
class ComplexGraphicsModel : public GraphicsModel {
 private:
  static ComplexGraphicsModel *LoadFromFile(std::string path);

 public:
  static ComplexGraphicsModel *LoadFromOBJ(std::string path);
  static ComplexGraphicsModel *LoadFromOBJ(std::string path, glm::vec3 color);

  void computeNormals();

  void setVertex(int index, glm::vec3 value);

  ComplexGraphicsModel *clone();
};
}

#endif //PGR_PROJECT_COMPLEXGRAPHICSMODEL_H
