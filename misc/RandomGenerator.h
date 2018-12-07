//
// Created by kuro on 7.12.18.
//

#ifndef PGR_PROJECT_RANDOMGENERATOR_H
#define PGR_PROJECT_RANDOMGENERATOR_H

#include <ctime>
#include <cstdlib>

class RandomGenerator{
private:
    RandomGenerator(){
        srand(static_cast<unsigned int>(time(nullptr)));
    };
public:
    static RandomGenerator& getInstance(){
        static RandomGenerator instance;
        return instance;
    }

    static float getRandomNumber(){
        return static_cast<float>(rand() / (double) RAND_MAX);
    }
};

#endif //PGR_PROJECT_RANDOMGENERATOR_H
