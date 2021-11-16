#include "config.h"
#include "ShaderResource.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

ShaderResource::ShaderResource()
{
}

ShaderResource::~ShaderResource()
{
    glDeleteProgram(program);
}

std::string ReadShader(const char* filePath) {
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);

    if (!fileStream.is_open()) {
        std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while (!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}

GLuint ShaderResource::LoadShader(const char* vertex_path, const char* fragment_path) {
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glActiveTexture(GL_TEXTURE0);

    // Read shaders

    std::string vertShaderStr = ReadShader(vertex_path);
    std::string fragShaderStr = ReadShader(fragment_path);
    const char* vertShaderSrc = vertShaderStr.c_str();
    const char* fragShaderSrc = fragShaderStr.c_str();

    GLint result = GL_FALSE;
    int logLength;

    // Compile vertex shader

    std::cout << "Compiling vertex shader." << std::endl;
    glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
    glCompileShader(vertShader);

    // Check vertex shader

    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> vertShaderError((logLength > 1) ? logLength : 1);
    glGetShaderInfoLog(vertShader, logLength, NULL, &vertShaderError[0]);
    std::cout << &vertShaderError[0] << std::endl;

    // Compile fragment shader

    std::cout << "Compiling fragment shader." << std::endl;
    glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
    glCompileShader(fragShader);

    // Check fragment shader

    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> fragShaderError((logLength > 1) ? logLength : 1);
    glGetShaderInfoLog(fragShader, logLength, NULL, &fragShaderError[0]);
    std::cout << &fragShaderError[0] << std::endl;

    std::cout << "Linking program" << std::endl;
    program = glCreateProgram();
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &result);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> programError((logLength > 1) ? logLength : 1);
    glGetProgramInfoLog(program, logLength, NULL, &programError[0]);
    std::cout << &programError[0] << std::endl;

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    return program;
}

void ShaderResource::BindShader() {
    glUseProgram(program);
}

void ShaderResource::setFloat(float floatIn, std::string uniform) {
    glUseProgram(program);
    glUniform1f(glGetUniformLocation(program, uniform.c_str()), floatIn);
}

void ShaderResource::setVec3(VectorMath3 vec3, std::string uniform) {
    glUseProgram(program);
    glUniform3fv(glGetUniformLocation(program, uniform.c_str()), 1, (float*)&vec3);
}

void ShaderResource::setVec4(VectorMath4 vec4, std::string uniform) {
    glUseProgram(program);
    glUniform4fv(glGetUniformLocation(program, uniform.c_str()), 1, (float*)&vec4);
}

void ShaderResource::setMat4(MatrixMath mat4, std::string uniform) {
    glUseProgram(program);
    glUniformMatrix4fv(glGetUniformLocation(program, uniform.c_str()), 1, GL_FALSE, (float*)&(mat4));
}

void ShaderResource::setLights(VectorMath3 lightColor[16], VectorMath3 lightPos[16], float intensity[16], int amountOfLights){
    glUseProgram(program);

    glUniform3fv(glGetUniformLocation(program, "lightColor"), amountOfLights, (float*)lightColor);
    glUniform3fv(glGetUniformLocation(program, "lightPos"), amountOfLights, (float*)lightPos);
    glUniform1fv(glGetUniformLocation(program, "intensity"), amountOfLights, (float*)intensity);
    glUniform1f(glGetUniformLocation(program, "amountOfLights"), amountOfLights);
    
}
