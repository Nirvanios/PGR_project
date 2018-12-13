#pragma once

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

namespace PGRgraphics {
/**
 * Class for loading, and compiling shader files
 *
 * @author Igor Frank
 */
class Shader {
private:

    GLuint shaderProgram;
    GLuint vertexshader, fragmentShader;

    std::string ReadFile(std::string *file);

    bool LoadVertexShader(std::string filename);

    bool LoadFragmentShader(std::string filename);

    void PrintShaderLinkingError(int32_t shaderId);

    void PrintShaderCompilationErrorInfo(int32_t shaderId);

    bool LinkShaders();

 public:

  GLuint getUniformLocation(const std::string uniform);

  void BindAttributeLocation(int index, const std::string &attribute);

  void UseProgram();

  bool Init();

  void CleanUp();

};
}
