#include "shader.h"
#include <GLEW/glew.h>
#include <iostream>
#include <string>
#include <fstream>


Shader::~Shader() {
	glDeleteShader(shader_id);
    glDeleteProgram(shader_id); // deleting program
}

Shader::Shader(const std::string path , const unsigned int shaderType) : program_id(glCreateProgram()) , shader_id(glCreateShader(shaderType)) {
    
    std::string source = getShader(path);
    const char* c_source = source.c_str();    
    glShaderSource(shader_id, 1, &c_source, nullptr); // shader id , count , GLSL code , lenght = auto = have null bit at end
    glCompileShader(shader_id);

    int result;

    // glGetShaderiv = get info about a shader
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result); // glGetShader == i = int / v = vector|pointer
    if (!result) {
        int length;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);
        char* errMessage = (char*)alloca(length * sizeof(char)); // allocate on the stack with alloca
        glGetShaderInfoLog(shader_id, length, &length, errMessage);
        std::cout << "Ho shit an error when compiling " << (shaderType == GL_FRAGMENT_SHADER ? "fragment" : "vertex") << " shader: " << std::endl;
        std::cout << errMessage << std::endl;

    }
    else {

        glAttachShader(program_id, shader_id);
        glLinkProgram(program_id);
        glValidateProgram(program_id);

    }

}

Shader::Shader(const std::string path, const unsigned int shaderType , unsigned int program) : program_id(program), shader_id(glCreateShader(shaderType)) {

    std::string source = getShader(path);
    const char* c_source = source.c_str();
    glShaderSource(shader_id, 1, &c_source, nullptr); // shader id , count , GLSL code , lenght = auto = have null bit at end
    glCompileShader(shader_id);

    int result;

    // glGetShaderiv = get info about a shader
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result); // glGetShader == i = int / v = vector|pointer
    if (!result) {
        int length;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);
        char* errMessage = (char*)alloca(length * sizeof(char)); // allocate on the stack with alloca
        glGetShaderInfoLog(shader_id, length, &length, errMessage);
        std::cout << "Ho shit an error when compiling " << (shaderType == GL_FRAGMENT_SHADER ? "fragment" : "vertex") << " shader: " << std::endl;
        std::cout << errMessage << std::endl;

    }
    else {

        glAttachShader(program_id, shader_id);
        glLinkProgram(program_id);
        glValidateProgram(program_id);

    }

   glUseProgram(program_id);

}

std::string Shader::getShader(const std::string& path) {
    std::ifstream stream(path); 
    if (!stream) {
        std::cout << path << " doesn't exist !" << std::endl;
        return "";
    }
    std::string content;
    std::string line;
    while (std::getline(stream, line)) { 
        content += line + "\n";
    }

    return content;
}

void Shader::bindProgram() {
    glUseProgram(program_id);
}

void Shader::unbindProgram(){
    glUseProgram(0);
}

unsigned int Shader::getProgram() {
    return program_id;
}

/*
static std::string getShader(const std::string& path) {

    std::ifstream stream(path); // ifstream = input file stream
    if (!stream) {
        // File could not be opened
        std::cout << path << " doesn't exist !" << std::endl;
        return "";
    }
    std::string content;
    std::string line;
    while (std::getline(stream , line)) { // check if line exist and change line var to content of current line
        content += line + "\n";
    }
    return content;
}


void createShader(const std::string& source, unsigned int type , unsigned int& program) {

    unsigned int s_id = glCreateShader(type);
    const char* c_source = source.c_str();
    glShaderSource(s_id, 1 , &c_source, nullptr); // shader id , count , GLSL code , lenght = auto = have null bit at end
    glCompileShader(s_id);

    int result;

    // glGetShaderiv = get info about a shader
    glGetShaderiv(s_id, GL_COMPILE_STATUS, &result); // glGetShader == i = int / v = vector|pointer
    if (!result) {
        int length;
        glGetShaderiv(s_id, GL_INFO_LOG_LENGTH, &length);
        char* errMessage = (char*)alloca(length * sizeof(char)); // allocate on the stack with alloca
        glGetShaderInfoLog(s_id, length, &length, errMessage);
        std::cout << "Ho shit an error when compiling " << (type == GL_FRAGMENT_SHADER ? "fragment" : "vertex") << " shader: " << std::endl;
        std::cout << errMessage << std::endl;

    }
    else {

        glAttachShader(program, s_id);
        glLinkProgram(program);
        glValidateProgram(program);

    }

        glDeleteShader(s_id);
}

void setFragmentShader(const std::string& source , unsigned int& program) {
    createShader(source, GL_FRAGMENT_SHADER, program);

}

void setVertexShader(const std::string& source, unsigned int& program) {
    createShader(source, GL_VERTEX_SHADER , program);
}



*/