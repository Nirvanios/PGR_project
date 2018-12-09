//
// Created by Petr Flajsingr on 2018-12-04.
//

#include "StdoutLogger.h"

void StdoutLogger::log(std::string &str) {
#ifdef PGR_LOG
  log(str.data());
#endif
}

void StdoutLogger::logTime(std::string &str) {
#ifdef PGR_LOG
  logTime(str.data());
#endif
}

void StdoutLogger::log(char *str) {
#ifdef PGR_LOG
  std::cout << str << std::endl;
#endif
}

std::string current_time() {
  time_t now = time(NULL);
  struct tm tstruct;
  char buf[40];
  tstruct = *localtime(&now);
  //format: HH:mm:ss
  strftime(buf, sizeof(buf), "%X", &tstruct);
  return buf;
}

void StdoutLogger::logTime(char *str) {
#ifdef PGR_LOG
  auto timenow = current_time();

  std::cout << timenow << ":\t" << str << std::endl;
#endif
}

void StdoutLogger::log(int val) {
#ifdef PGR_LOG
  std::cout << "integer" << ":\t" << val << std::endl;
#endif
}

void StdoutLogger::log(glm::vec3 vector) {
#ifdef PGR_LOG
  std::cout << "vec3" << ":\t" << vector.x << " " << vector.y << " " << vector.z << std::endl;
#endif
}

void StdoutLogger::log(float value) {
#ifdef PGR_LOG
  std::cout << "float" << ":\t" << value << std::endl;
#endif
}
void StdoutLogger::log(glm::vec2 vector) {
#ifdef PGR_LOG
  std::cout << "vec2" << ":\t" << vector.x << " " << vector.y << std::endl;
#endif
}

void StdoutLogger::log(char *str, float val) {
#ifdef PGR_LOG
  std::cout << str << val << std::endl;
#endif
}

void StdoutLogger::log(char *str, glm::vec3 &vector) {
#ifdef PGR_LOG
  std::cout << str << "\t" << vector.x << " " << vector.y << " " << vector.z << std::endl;
#endif
}


