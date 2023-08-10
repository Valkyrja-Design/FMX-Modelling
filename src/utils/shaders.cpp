#include "shaders.h"

#include <fstream>
#include <sstream>

Shader :: Shader(const std::string& VertexShaderPath, const std::string& FragShaderPath){

    std::string vertexShaderCode;
    std::string fragShaderCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ios_base::failbit | std::ios_base::badbit);
    fShaderFile.exceptions(std::ios_base::failbit | std::ios_base::badbit);

    try {
        vShaderFile.open(VertexShaderPath);
        fShaderFile.open(FragShaderPath);
        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vertexShaderCode = vShaderStream.str();
        fragShaderCode = fShaderStream.str();

    } catch (std::ifstream::failure e){
        std::cout << "ERROR::FAILED TO READ SHADER FILES\n" << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    const char* vShaderSource = vertexShaderCode.c_str();
    const char* fShaderSource = fragShaderCode.c_str();
    unsigned int vertex;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderSource, nullptr);
    glCompileShader(vertex);


    checkCompilationStatus(vertex, 1);

    unsigned int fragment;
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderSource, nullptr);
    glCompileShader(fragment);

    checkCompilationStatus(fragment, 2);

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    checkCompilationStatus(ID, 0);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader :: use() const {
    glUseProgram(ID);
}

void Shader :: checkCompilationStatus(unsigned int entity, int type) const {
    int success;
    char info[512];

    if (type){
        glGetShaderiv(entity, GL_COMPILE_STATUS, &success);
        
        if (!success){
            glGetShaderInfoLog(entity, 512, nullptr, info);
            std::cout << "ERROR::SHADER::" << (type == 1 ? "VEXTEX::" : "FRAGMENT::") << "COMPILATION FAILED\n" << info << std::endl;
        }
    } else{
        glGetProgramiv(entity, GL_LINK_STATUS, &success);

        if (!success){
            glGetProgramInfoLog(entity, 512, nullptr, info);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING FAILED\n" << info << std::endl;
        }
    }   
}

