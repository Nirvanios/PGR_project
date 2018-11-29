cmake_minimum_required(VERSION 3.12)
project(PGR_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(SDL2_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/libs/SDL2/include)
set(SDL2_LIB_DIR ${PROJECT_SOURCE_DIR}/libs/SDL2/lib/x64)

# set paths (only needed on windows)
if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    # where is the SDL2 development package copied to?
    set(SDL2_PATH ${PROJECT_SOURCE_DIR}/libs/SDL2)
endif()

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})


find_package (OpenGL REQUIRED)


if(WIN32)
    set(GLEW_INCLUDE_DIR ${PROJECT_SOURCE_DIR}\\libs\\glew\\include)
    set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}\\libs\\glew")
    set(CMAKE_LIBRARY_PATH "${CMAKE_SOURCE_DIR}\\libs\\glew\\lib")
endif()


find_path(GLEW_INCLUDE_DIR GL/glew.h)
find_library(GLEW_LIBRARY NAMES GLEW glew32 glew glew32s PATH_SUFFIXES lib64)
set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/libs/glew)
set(CMAKE_LIBRARY_PATH ${PROJECT_SOURCE_DIR}/libs/glew/lib/Release/x64/)

find_package(GLEW REQUIRED)

if(GLEW_FOUND)

    message("GLEW Found!")

    include_directories(${GLEW_INCLUDE_DIRS})

    link_libraries(${GLEW_LIBRARIES})

    add_definitions(${GLEW_DEFINITIONS})

else(GLEW_FOUND)

    message(FATAL_ERROR "GLEW NOT Found")

endif(GLEW_FOUND)

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
    target_link_libraries(PGR_project SDL2main SDL2 ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLM_LIBRARIES})
endif()