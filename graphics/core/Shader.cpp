//
// Created by Igor Frank on 13.12.18.
//

#include <StdoutLogger.h>
#include "Shader.h"

std::string PGRgraphics::Shader::ReadFile(std::string *file) {

    std::ifstream t(*file);

    std::stringstream buffer;
    buffer << t.rdbuf();

    std::string fileContent = buffer.str();

    return fileContent;
  }

GLuint PGRgraphics::Shader::getUniformLocation(const std::string uniform) {
    return glGetUniformLocation(shaderProgram, uniform.c_str());
}

void PGRgraphics::Shader::BindAttributeLocation(int index, const std::string &attribute) {
    glBindAttribLocation(shaderProgram, index, attribute.c_str());
}

void PGRgraphics::Shader::UseProgram() {
    glUseProgram(shaderProgram);
}

bool PGRgraphics::Shader::Init() {
    shaderProgram = glCreateProgram();

    // Bind the location attributes
    BindAttributeLocation(0, "inputPosition");
    BindAttributeLocation(2, "inputTexCoord");
    BindAttributeLocation(1, "inputNormal");

    if (!LoadVertexShader("../graphics/shaders/main_vertex_shader.glsl"))
        return false;

    if (!LoadFragmentShader("../graphics/shaders/main_fragment_shader.glsl"))
        return false;

    return LinkShaders();
}

bool PGRgraphics::Shader::LoadVertexShader(std::string filename) {
    StdoutLogger::getInstance().logTime(const_cast<char *>("Loading vertex shader..."));

    std::string str = ReadFile(&filename);

    char *src = const_cast<char *>( str.c_str());
    int  size = static_cast<int>(str.length());

    vertexshader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexshader, 1, &src, &size);

    glCompileShader(vertexshader);

    int status = 0;
    glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &status);

    if (status == 0) {
        PrintShaderCompilationErrorInfo(vertexshader);
        return false;
    }

    glAttachShader(shaderProgram, vertexshader);
    return true;
}

bool PGRgraphics::Shader::LoadFragmentShader(std::string filename) {
    StdoutLogger::getInstance().logTime(const_cast<char *>("Loading vertex shader..."));

    std::string str = ReadFile(&filename);

    char *src = const_cast<char *>( str.c_str());
    int size = static_cast<int>(str.length());

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &src, &size);

    glCompileShader(fragmentShader);

    int wasCompiled = 0;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &wasCompiled);

    if (wasCompiled == false) {
        PrintShaderCompilationErrorInfo(fragmentShader);
        return false;
    }

    glAttachShader(shaderProgram, fragmentShader);
    return true;
}

bool PGRgraphics::Shader::LinkShaders() {
    glLinkProgram(shaderProgram);

    int isLinked;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, (int *) &isLinked);

    if (isLinked == false)
        PrintShaderLinkingError(shaderProgram);

    return isLinked != 0;
}

void PGRgraphics::Shader::PrintShaderLinkingError(int32_t shaderId) {
    std::cout << "=======================================\n";
    std::cout << "Shader linking failed : " << std::endl;

    // Find length of shader info log
    int maxLength;
    glGetProgramiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

    std::cout << "Info Length : " << maxLength << std::endl;

    // Get shader info log
    char *shaderProgramInfoLog = new char[maxLength];
    glGetProgramInfoLog(shaderProgram, maxLength, &maxLength, shaderProgramInfoLog);

    std::cout << "Linker error message : " << shaderProgramInfoLog << std::endl;

    /* Handle the error in an appropriate way such as displaying a message or writing to a log file. */
    /* In this simple program, we'll just leave */
    delete[] shaderProgramInfoLog;
    return;
}

void PGRgraphics::Shader::PrintShaderCompilationErrorInfo(int32_t shaderId) {
    std::cout << "=======================================\n";
    std::cout << "Shader compilation failed : " << std::endl;

    // Find length of shader info log
    int maxLength;
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

    // Get shader info log
    char *shaderInfoLog = new char[maxLength];
    glGetShaderInfoLog(shaderId, maxLength, &maxLength, shaderInfoLog);

    // Print shader info log
    std::cout << "\tError info : " << shaderInfoLog << std::endl;

    std::cout << "=======================================\n\n";
    delete[] shaderInfoLog;
}

void PGRgraphics::Shader::CleanUp() {
    /* Cleanup all the things we bound and allocated */
    glUseProgram(0);
    glDetachShader(shaderProgram, vertexshader);
    glDetachShader(shaderProgram, fragmentShader);

    glDeleteProgram(shaderProgram);

    glDeleteShader(vertexshader);
    glDeleteShader(fragmentShader);
}

