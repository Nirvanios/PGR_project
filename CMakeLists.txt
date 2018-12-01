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

include_directories(simulation/base simulation/common simulation/forces simulation/integrators simulation/objects simulation)

add_executable(sim_test sim_test_main.cpp simulation/base/SimulatedObject.h simulation/objects/Constraint.h
        simulation/common/common.h simulation/objects/SimulatedModel.cpp simulation/objects/SimulatedModel.h
        simulation/base/ForceGenerator.h simulation/forces/GravityForce.cpp simulation/forces/GravityForce.h
        simulation/forces/DragForce.cpp simulation/forces/DragForce.h simulation/forces/Spring.cpp
        simulation/forces/Spring.h simulation/base/Integrator.h simulation/integrators/EulerIntegrator.cpp
        simulation/integrators/EulerIntegrator.h simulation/Simulation.cpp simulation/Simulation.h
        simulation/objects/PointConstraint.cpp simulation/objects/PointConstraint.h simulation/objects/LengthConstraint.cpp
        simulation/objects/LengthConstraint.h simulation/integrators/VerletIntegrator.cpp simulation/integrators/VerletIntegrator.h
        simulation/objects/SimulatedVertex.cpp simulation/objects/SimulatedVertex.h simulation/SoftBodySimulation.cpp
        simulation/SoftBodySimulation.h simulation/ClothSimulation.cpp simulation/ClothSimulation.h simulation/forces/ConstantForce.cpp simulation/forces/ConstantForce.h)

target_link_libraries(sim_test ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES}  ${GLM_LIBRARIES})

add_executable(PGR_project test.cpp simulation/base/SimulatedObject.h simulation/objects/Constraint.h
        simulation/common/common.h simulation/objects/SimulatedModel.cpp simulation/objects/SimulatedModel.h
        simulation/base/ForceGenerator.h simulation/forces/GravityForce.cpp simulation/forces/GravityForce.h
        simulation/forces/DragForce.cpp simulation/forces/DragForce.h simulation/forces/Spring.cpp
        simulation/forces/Spring.h simulation/base/Integrator.h simulation/integrators/EulerIntegrator.cpp
        simulation/integrators/EulerIntegrator.h simulation/Simulation.cpp simulation/Simulation.h sim_test_main.cpp
        simulation/objects/PointConstraint.cpp simulation/objects/PointConstraint.h simulation/objects/LengthConstraint.cpp
        simulation/objects/LengthConstraint.h simulation/integrators/VerletIntegrator.cpp simulation/integrators/VerletIntegrator.h simulation/objects/SimulatedVertex.cpp simulation/objects/SimulatedVertex.h simulation/SoftBodySimulation.cpp simulation/SoftBodySimulation.h simulation/ClothSimulation.cpp simulation/ClothSimulation.h simulation/forces/ConstantForce.cpp simulation/forces/ConstantForce.h)

target_link_libraries(PGR_project ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES}  ${GLM_LIBRARIES})
