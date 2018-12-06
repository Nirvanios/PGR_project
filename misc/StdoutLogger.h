//
// Created by Petr Flajsingr on 2018-12-04.
//

#ifndef PGR_PROJECT_STDOUTLOGGER_H
#define PGR_PROJECT_STDOUTLOGGER_H

#include "Logger.h"
#include <iostream>

class StdoutLogger : public Logger {
 private:
  StdoutLogger() = default;
 public:

  static StdoutLogger &getInstance() {
    static StdoutLogger instance;

    return instance;
  }

  void log(std::string &str) override;
  void logTime(std::string &str) override;
  void log(char *str) override;
  void logTime(char *str) override;
  void log(int val) override;

};

#endif //PGR_PROJECT_STDOUTLOGGER_H
