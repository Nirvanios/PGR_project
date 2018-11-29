cmake_minimum_required(VERSION 3.12)
project(PGR_project)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

add_definitions(-DGLEW_STATIC)

set(SDL2_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}\\libs\\win64-SDL2\\include)
set(SDL2_PATH ${PROJECT_SOURCE_DIR}\\libs\\win64-SDL2)

#set(GLEW_INCLUDE_DIR ${PROJECT_SOURCE_DIR}\\libs\\glew\\include)
#set(GLEW_LIBRARY ${PROJECT_SOURCE_DIR}\\libs\\glew\\lib\\libglew32.a)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
if(WIN32)
    link_directories(${PROJECT_SOURCE_DIR}/libs/win64-SDL2/lib)
endif()

find_package (OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

set(GLEW_INCLUDE_DIR ${PROJECT_SOURCE_DIR}\\libs\\glew\\include)
set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}\\libs\\glew")
set(CMAKE_LIBRARY_PATH "${CMAKE_SOURCE_DIR}\\libs\\glew\\lib")
find_package(GLEW REQUIRED)

if(GLEW_FOUND)

    message("GLEW Found!")

    include_directories(${GLEW_INCLUDE_DIRS})

    link_libraries(${GLEW_LIBRARIES})

    add_definitions(${GLEW_DEFINITIONS})

else(GLEW_FOUND)

    message(FATAL_ERROR "GLEW NOT Found")

endif(GLEW_FOUND)
link_libraries(${GLEW_LIBRARIES})


find_package(glm REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})

add_executable(PGR_project main.cpp simulation/base/SimulatedObject.h simulation/objects/Constraint.cpp simulation/objects/Constraint.h
        simulation/common/common.h simulation/objects/SimulatedModel.cpp simulation/objects/SimulatedModel.h
        simulation/base/ForceGenerator.h simulation/forces/GravityForce.cpp simulation/forces/GravityForce.h
        simulation/forces/DragForce.cpp simulation/forces/DragForce.h simulation/forces/Spring.cpp
        simulation/forces/Spring.h simulation/base/Integrator.h simulation/integrators/EulerIntegrator.cpp
        simulation/integrators/EulerIntegrator.h simulation/Simulation.cpp simulation/Simulation.h)

if(APPLE)
    target_link_libraries(PGR_project SDL2main SDL2 ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES}  ${GLM_LIBRARIES})
elseif(WIN32)
    target_link_libraries(PGR_project mingw32 SDL2main SDL2 glew32 ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLM_LIBRARIES})
endif()