cmake_minimum_required(VERSION 3.12)
project(PGR_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")

if (FALSE AND APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
endif ()

add_compile_definitions(GLM_ENABLE_EXPERIMENTAL)
add_compile_definitions(PGR_LOG)

find_package( Threads )

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
        simulation/objects simulation graphics graphics/Camera graphics/objects misc)

FILE(GLOB_RECURSE SOURCE_FILES misc/*.cpp graphics/*.cpp misc/*.cpp simulation/*.cpp third_party/*.cpp)
FILE(GLOB_RECURSE HEADER_FILES misc/*.h graphics/*.h misc/*.h simulation/*.h third_party/*.h)

add_executable(collision_demo main_collision_demo.cpp
        ${SOURCE_FILES} ${HEADER_FILES})

add_executable(tear_demo main_tear_demo.cpp
        ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(collision_demo ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLM_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(tear_demo ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLM_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

file(GLOB RESOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/*)

file(COPY ${RESOURCE_FILES}
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
