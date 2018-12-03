//
// Created by kuro on 2.12.18.
//

#ifndef PGR_PROJECT_SIMPLEGRAPHICSMODELCREATOR_H
#define PGR_PROJECT_SIMPLEGRAPHICSMODELCREATOR_H


#include <vector>
#include "SimpleGraphicsModel.h"
#include "SoftBodyGraphicsModel.h"

class SimpleGraphicsModelCreator {

public:
        static SimpleGraphicsModel* CreateQuad(float width, float height, float depth, float tx, float ty, float tz){
            float vertices[] = {(width/2), (height/2), (depth/2),
                                (width/2), -(height/2), (depth/2),
                                -(width/2), (height/2), (depth/2),
                                -(width/2), -(height/2), (depth/2),

                                (width/2), (height/2), -(depth/2),
                                (width/2), -(height/2), -(depth/2),
                                -(width/2), (height/2), -(depth/2),
                                -(width/2), -(height/2), -(depth/2)};

            unsigned char indicies[] = {0, 1, 3,
                                0, 2, 3,
                                4,5,7,
                                4,6,7,
                                4,2,0,
                                4,6,2,
                                5,3,1,
                                5,7,3,
                                2,7,3,
                                2,7,6,
                                0,5,1,
                                0,5,4
            };
            glm::vec3 position = glm::vec3(tx, ty, tz);
            return new SimpleGraphicsModel(position, vertices, 24, indicies, 36);
        }

        static SimpleGraphicsModel* createLine(glm::vec3 start, glm::vec3 end){
            float vertices [] = {start.x, start.y, start.z,
                                end.x, end.y, end.z
            };

            unsigned char indicies [] = {0,0,1,
                                 1,1,0
            };
            auto position = glm::vec3(0.0f);
            auto model = new SimpleGraphicsModel(position, vertices, 6, indicies, 6);
            model->setIsLine(true);
            return model;
        }

        static SoftBodyGraphicsModel* createCloth(float width, float height, int widthVertices, int heightVertices){
            float *vertices = new float[widthVertices*heightVertices*3];
            float yStep = width/(widthVertices-1);
            float xStep = height/(heightVertices-1);
            int pos =0;
            for(float i = -(width/2); i < width; i+=yStep){
                for (float j = (-width/2); j < height; j+=xStep){
                    vertices[pos] = j;
                    vertices[pos+1] = 0;
                    vertices[pos+2] = i;
                }
            }
        }
};


#endif //PGR_PROJECT_SIMPLEGRAPHICSMODELCREATOR_H
