cmake_minimum_required(VERSION 3.10)
project(PGR_project)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
#set(SDL2_PATH  ${PROJECT_SOURCE_DIR}"\\libs\\i686_64-w64-mingw32")
set(SDL2_INCLUDE_DIRS "C:\\Users\\Petr\\CLionProjects\\PGR project\\libs\\win64-SDL2\\include")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
link_directories("C:\\Users\\Petr\\CLionProjects\\PGR project\\libs\\win64-SDL2\\lib")

find_package (OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR}  ${GLUT_INCLUDE_DIRS})


set(CMAKE_PREFIX_PATH "C:\\Users\\Petr\\CLionProjects\\PGR project\\libs\\GLEW")
set(CMAKE_LIBRARY_PATH "C:\\Users\\Petr\\CLionProjects\\PGR project\\libs\\GLEW\\lib\\Release\\Win32")

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories($(GLEW_INCLUDE_DIRS))
endif()

add_executable(PGR_project main.cpp SimulatedObject.cpp SimulatedObject.h)
target_link_libraries(PGR_project mingw32 SDL2main SDL2 ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})