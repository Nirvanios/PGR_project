#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc32-c"
//
// Created by kuro on 7.12.18.
//

#ifndef PGR_PROJECT_RANDOMGENERATOR_H
#define PGR_PROJECT_RANDOMGENERATOR_H

#include <random>
#include <ctime>

/**
 * Random number generator seeded with system time.
 *
 * @author Igor Frank
 */
class RandomGenerator{
private:
  RandomGenerator(){
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
  };
public:
  static RandomGenerator& getInstance(){
    static RandomGenerator instance;
    return instance;
  }

  static float getRandomNumber(){
    return static_cast<float>(std::rand() / (double) RAND_MAX);
  }
};

#endif //PGR_PROJECT_RANDOMGENERATOR_H

#pragma clang diagnostic pop