#pragma once
#include <string>

#include "glad/glad.h"

namespace Renderer
{
    class ShaderProgram
    {
    public:
        ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
        ~ShaderProgram();
        bool IsCompiled() const { return isCompiled; }
        void Use() const;

        ShaderProgram();
        ShaderProgram(ShaderProgram&);
        ShaderProgram& operator=(const ShaderProgram&) = delete;
        ShaderProgram& operator=(ShaderProgram&&) noexcept;
        ShaderProgram(ShaderProgram&& shaderProgram) noexcept;
        
    private:
        bool isCompiled = false;
        GLuint ID = 0;

        bool CreateShader(const std::string &src, const GLenum shaderType, GLuint &shaderID);
    };
}
