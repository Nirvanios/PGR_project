cmake_minimum_required(VERSION 3.10)
project(PGR_project)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(SDL2_INCLUDE_DIRS "C:\\Users\\Petr\\CLionProjects\\PGR project\\libs\\win64-SDL2\\include")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
link_directories("C:\\Users\\Petr\\CLionProjects\\PGR project\\libs\\win64-SDL2\\lib")

find_package (OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIRS})




find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

find_package(glm REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})

add_executable(PGR_project main.cpp simulation/base/SimulatedObject.h simulation/Constraint.cpp simulation/Constraint.h simulation/common/common.h simulation/SimulatedModel.cpp simulation/SimulatedModel.h simulation/base/ForceGenerator.h simulation/GravityForce.cpp simulation/GravityForce.h)
target_link_libraries(PGR_project mingw32 SDL2main SDL2 ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES}  ${GLM_LIBRARIES})