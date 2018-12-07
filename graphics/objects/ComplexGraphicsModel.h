//
// Created by Petr Flajsingr on 2018-12-04.
//

#ifndef PGR_PROJECT_COMPLEXGRAPHICSMODEL_H
#define PGR_PROJECT_COMPLEXGRAPHICSMODEL_H

#include <StdoutLogger.h>
#include "GraphicsModel.h"
#include <algorithm>

namespace PGRgraphics {

class ComplexGraphicsModel : public GraphicsModel {
 private:
 protected:
 public:

  void computeNormals();

  static ComplexGraphicsModel *LoadFromOBJ(std::string path);

  void setVertex(int index, glm::vec3 value);

  ComplexGraphicsModel *clone();
};
}

#endif //PGR_PROJECT_COMPLEXGRAPHICSMODEL_H
