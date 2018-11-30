cmake_minimum_required(VERSION 3.12)
project(PGR_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIRS})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

find_package(glm REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})

add_executable(PGR_project test.cpp simulation/base/SimulatedObject.h simulation/objects/Constraint.cpp simulation/objects/Constraint.h
        simulation/common/common.h simulation/objects/SimulatedModel.cpp simulation/objects/SimulatedModel.h
        simulation/base/ForceGenerator.h simulation/forces/GravityForce.cpp simulation/forces/GravityForce.h
        simulation/forces/DragForce.cpp simulation/forces/DragForce.h simulation/forces/Spring.cpp
        simulation/forces/Spring.h simulation/base/Integrator.h simulation/integrators/EulerIntegrator.cpp
        simulation/integrators/EulerIntegrator.h simulation/Simulation.cpp simulation/Simulation.h)

target_link_libraries(PGR_project ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES}  ${GLM_LIBRARIES})
