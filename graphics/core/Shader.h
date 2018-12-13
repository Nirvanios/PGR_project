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

        /**
         * Reads file as string
         * @param file file to read
         * @return content of file
         */
        std::string ReadFile(std::string *file);

        /**
         * Loads vertex shader
         * @param filename vertex shader file to load
         * @return true if no error else false
         */
        bool LoadVertexShader(std::string filename);

        /**
         * Loads fragment shader
         * @param filename fragment shader file to load
         * @return true if no error else false
         */
        bool LoadFragmentShader(std::string filename);

        /**
         * Prints error during shader linking
         * @param shaderId shader program ID
         */
        void PrintShaderLinkingError(int32_t shaderId);

        /**
         * Prints error during shader compilation
         * @param shaderId shader program ID
         */
        void PrintShaderCompilationErrorInfo(int32_t shaderId);

        /**
         * Link shaders and checks for error
         * @return true if no error else false
         */
        bool LinkShaders();

    public:

        /**
         * Returns uniform location id inside shader
         * @param uniform name of uniform parametr in shader
         * @return uniform location id
         */
        GLuint getUniformLocation(const std::string uniform);

        /**
         * Bind attribute location to index
         * @param index index of attribute
         * @param attribute Name of attribute in shader
         */
        void BindAttributeLocation(int index, const std::string &attribute);

        /**
         * Selects created program
         */
        void UseProgram();

        /**
         * Initialize shaders - loads files, bind attributes and link shaders
         * @return true if no error else false
         */
        bool Init();

        /**
         * Free resources
         */
        void CleanUp();

    };
}
