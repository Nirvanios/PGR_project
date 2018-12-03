//
// Created by kuro on 2.12.18.
//

#ifndef PGR_PROJECT_SOFTBODYGRAPHICSMODEL_H
#define PGR_PROJECT_SOFTBODYGRAPHICSMODEL_H



class SoftBodyGraphicsModel {
private:
    float * vertices;
    int verticesSize;

    uint8_t indicies;
    int indiciesSize;

public:
    SoftBodyGraphicsModel(float *vertices, int verticesSize, uint8_t indicies, int indiciesSize) :
            vertices(vertices) ,verticesSize(verticesSize), indicies(indicies), indiciesSize(indiciesSize){
    }
};


#endif //PGR_PROJECT_SOFTBODYGRAPHICSMODEL_H
