#include "ShaderProgram.h"

#include <iostream>

namespace Renderer
{
    ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
    {
        GLuint vertexShaderID;
        if(!CreateShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID))
        {
            std::cerr << "VERTEX SHADER compile time error" << std::endl;
            return;
        }

        GLuint fragmentShaderID;
        if(!CreateShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID))
        {
            std::cerr << "FRAGMENT SHADER compile time error" << std::endl;
            glDeleteShader(vertexShaderID);
            return;
        }

        ID = glCreateProgram();
        glAttachShader(ID, vertexShaderID);
        glAttachShader(ID, fragmentShaderID);
        glLinkProgram(ID);

        GLint status;
        glGetProgramiv(ID, GL_LINK_STATUS, &status);
        if(!status)
        {
            GLchar infoLog[1024];
            glGetShaderInfoLog(ID, 1024, nullptr, infoLog);
            std::cerr << "ERROR::SHADER: Link time error:\n" << infoLog << std::endl;
        }

        isCompiled = true;
        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);
    }

    bool ShaderProgram::CreateShader(const std::string& src, const GLenum shaderType, GLuint& shaderID)
    {
        shaderID = glCreateShader(shaderType);
        const char* code = src.c_str();
        
        glShaderSource(shaderID, 1, &code, nullptr);
        glCompileShader(shaderID);

        GLint status;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);

        if (!status)
        {
            GLchar infoLog[1024];
            glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
            std::cerr << "ERROR::SHADER: Compile time error:\n" << infoLog << std::endl;
            return false;
        }

        return true;
    }

    ShaderProgram::~ShaderProgram()
    {
        glDeleteProgram(ID);
    }

    void ShaderProgram::Use() const
    {
        glUseProgram(ID);
    }

    ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) noexcept
    {
        ID = shaderProgram.ID;
        isCompiled = shaderProgram.isCompiled;

        shaderProgram.ID = 0;
        shaderProgram.isCompiled = false;
    }

    ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shaderProgram) noexcept
    {
        glDeleteProgram(ID);
        ID = shaderProgram.ID;
        isCompiled = shaderProgram.isCompiled;

        shaderProgram.ID = 0;
        shaderProgram.isCompiled = false;

        return *this;
    }


}
