cmake_minimum_required(VERSION 3.12)
project(PGR_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

add_compile_definitions(GLM_ENABLE_EXPERIMENTAL)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIRS})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

find_package(glm REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})

include_directories(simulation/simulations simulation/base
        simulation/common simulation/forces simulation/integrators
        simulation/objects simulation graphics graphics/Camera graphics/objects)

add_executable(sim_test sim_test_main.cpp simulation/base/SimObject.h simulation/objects/SimpleObject.cpp simulation/objects/Constraint.h
        simulation/common/common.h simulation/objects/SimpleObject.h
        simulation/base/ForceGenerator.h simulation/forces/GravityForce.cpp simulation/forces/GravityForce.h
        simulation/forces/DragForce.cpp simulation/forces/DragForce.h simulation/forces/Spring.cpp
        simulation/forces/Spring.h simulation/base/Integrator.h simulation/integrators/EulerIntegrator.cpp
        simulation/integrators/EulerIntegrator.h simulation/simulations/Simulation.cpp simulation/simulations/Simulation.h
        simulation/objects/PointConstraint.cpp simulation/objects/PointConstraint.h simulation/objects/LengthConstraint.cpp
        simulation/objects/LengthConstraint.h simulation/integrators/VerletIntegrator.cpp simulation/integrators/VerletIntegrator.h
        simulation/objects/Vertex.cpp simulation/objects/Vertex.h simulation/simulations/SoftBodySimulation.cpp
        simulation/simulations/SoftBodySimulation.h simulation/simulations/ClothSimulation.cpp simulation/simulations/ClothSimulation.h
        simulation/forces/ConstantForce.cpp simulation/forces/ConstantForce.h graphics/objects/DEPRECATED_SimpleGraphicsModel.cpp graphics/objects/DEPRECATED_SimpleGraphicsModel.h simulation/simulations/GoalSoftBodySimulation.cpp simulation/simulations/GoalSoftBodySimulation.h simulation/forces/SnapableSpring.cpp simulation/forces/SnapableSpring.h simulation/collisions/CollisionObject.cpp simulation/collisions/CollisionObject.h simulation/objects/ComplexObject.cpp simulation/objects/ComplexObject.h)

target_link_libraries(sim_test ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES}  ${GLM_LIBRARIES})

add_executable(PGR_project test.cpp simulation/base/SimObject.h simulation/objects/SimpleObject.cpp simulation/objects/Constraint.h
        simulation/common/common.h simulation/objects/SimpleObject.h
        simulation/base/ForceGenerator.h simulation/forces/GravityForce.cpp simulation/forces/GravityForce.h
        simulation/forces/DragForce.cpp simulation/forces/DragForce.h simulation/forces/Spring.cpp
        simulation/forces/Spring.h simulation/base/Integrator.h simulation/integrators/EulerIntegrator.cpp
        simulation/integrators/EulerIntegrator.h simulation/simulations/Simulation.cpp simulation/simulations/Simulation.h sim_test_main.cpp
        simulation/objects/PointConstraint.cpp simulation/objects/PointConstraint.h simulation/objects/LengthConstraint.cpp
        simulation/objects/LengthConstraint.h simulation/integrators/VerletIntegrator.cpp simulation/integrators/VerletIntegrator.h
        simulation/objects/Vertex.cpp simulation/objects/Vertex.h simulation/simulations/SoftBodySimulation.cpp
        simulation/simulations/SoftBodySimulation.h simulation/simulations/ClothSimulation.cpp simulation/simulations/ClothSimulation.h
        simulation/forces/ConstantForce.cpp simulation/forces/ConstantForce.h graphics/objects/DEPRECATED_SimpleGraphicsModel.cpp graphics/objects/DEPRECATED_SimpleGraphicsModel.h simulation/simulations/GoalSoftBodySimulation.cpp simulation/simulations/GoalSoftBodySimulation.h graphics/objects/DEPRECATED_SimpleGraphicsModelCreator.cpp graphics/objects/DEPRECATED_SimpleGraphicsModelCreator.h graphics/camera/Camera.cpp graphics/camera/Camera.h simulation/forces/SnapableSpring.cpp simulation/forces/SnapableSpring.h simulation/collisions/CollisionObject.cpp simulation/collisions/CollisionObject.h simulation/objects/ComplexObject.cpp simulation/objects/ComplexObject.h graphics/objects/GraphicsModel.h graphics/objects/SimpleGraphicsModel.cpp graphics/objects/SimpleGraphicsModel.h)

target_link_libraries(PGR_project ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES}  ${GLM_LIBRARIES})

add_executable(Render_test MainWindow2.cpp shader.h
        graphics/objects/SimpleGraphicsModel.cpp
        graphics/objects/SimpleGraphicsModel.h
        simulation/base/SimObject.h simulation/objects/SimpleObject.cpp simulation/objects/Constraint.h
        simulation/common/common.h simulation/objects/SimpleObject.h
        simulation/base/ForceGenerator.h simulation/forces/GravityForce.cpp simulation/forces/GravityForce.h
        simulation/forces/DragForce.cpp simulation/forces/DragForce.h simulation/forces/Spring.cpp
        simulation/forces/Spring.h simulation/base/Integrator.h simulation/integrators/EulerIntegrator.cpp
        simulation/integrators/EulerIntegrator.h simulation/simulations/Simulation.cpp simulation/simulations/Simulation.h
        simulation/objects/PointConstraint.cpp simulation/objects/PointConstraint.h simulation/objects/LengthConstraint.cpp
        simulation/objects/LengthConstraint.h simulation/integrators/VerletIntegrator.cpp simulation/integrators/VerletIntegrator.h
        simulation/objects/Vertex.cpp simulation/objects/Vertex.h simulation/simulations/SoftBodySimulation.cpp
        simulation/simulations/SoftBodySimulation.h simulation/simulations/ClothSimulation.cpp simulation/simulations/ClothSimulation.h
        simulation/forces/ConstantForce.cpp simulation/forces/ConstantForce.h graphics/objects/DEPRECATED_SimpleGraphicsModel.cpp
        graphics/objects/DEPRECATED_SimpleGraphicsModel.h simulation/simulations/GoalSoftBodySimulation.cpp
        simulation/simulations/GoalSoftBodySimulation.h graphics/camera/Camera.cpp graphics/camera/Camera.h
        simulation/forces/SnapableSpring.cpp simulation/forces/SnapableSpring.h
        graphics/core/GraphicsCore.cpp simulation/collisions/CollisionObject.cpp simulation/collisions/CollisionObject.h
        simulation/objects/ComplexObject.cpp simulation/objects/ComplexObject.h
        graphics/objects/GraphicsModel.h simulation/objects/SimpleObject.h
        graphics/objects/tiny_obj_loader.h graphics/objects/tiny_obj_loader.cc)


target_link_libraries(Render_test ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES}  ${GLM_LIBRARIES})