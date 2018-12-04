//
// Created by Petr Flajsingr on 2018-12-04.
//

#ifndef PGR_PROJECT_LOGGER_H
#define PGR_PROJECT_LOGGER_H

#include <string>

class Logger {
 public:
  virtual void log(std::string &str) = 0;

  virtual void logTime(std::string &str) = 0;

  virtual void log(char *str) = 0;

  virtual void logTime(char *str) = 0;
};

#endif //PGR_PROJECT_LOGGER_H
