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
        bool isCompiled() const { return m_isCompiled; }
        void use() const;

        ShaderProgram();
        ShaderProgram(ShaderProgram&);
        ShaderProgram& operator=(const ShaderProgram&) = delete;
        ShaderProgram& operator=(ShaderProgram&&) noexcept;
        ShaderProgram(ShaderProgram&& shaderProgram) noexcept;
        
    private:
        bool m_isCompiled = false;
        GLuint m_ID = 0;

        bool createShader(const std::string &src, const GLenum shaderType, GLuint &shaderID);
    };
}
