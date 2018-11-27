cmake_minimum_required(VERSION 3.10)
project(PGR_project)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(SDL2_PATH  ${PROJECT_SOURCE_DIR}"\\libs\\i686_64-w64-mingw32")
set(SDL2_INCLUDE_DIRS "C:\\Users\\Petr\\CLionProjects\\PGR project\\libs\\i686-w64-mingw32\\include")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
link_directories("C:\\Users\\Petr\\CLionProjects\\PGR project\\libs\\i686-w64-mingw32\\lib")

find_package (OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR}  ${GLUT_INCLUDE_DIRS})

add_executable(PGR_project main.cpp SimulatedObject.cpp SimulatedObject.h)
target_link_libraries(PGR_project mingw32 SDL2main SDL2 ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})