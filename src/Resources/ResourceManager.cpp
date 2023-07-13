#include "ResourceManager.h"

#include <fstream>
#include <iostream>
#include <sstream>

namespace Renderer
{
    ResourceManager::ResourceManager(const std::string& executablePath)
    {
        const std::size_t separatorPosition = executablePath.find_last_of("/\\");
        path = executablePath.substr(0, separatorPosition);
    }

    std::string ResourceManager::GetShaderCode(const std::string& relativePath) const
    {
        std::ifstream stream;
        stream.open(path + "/" + relativePath, std::ios::in | std::ios::binary);

        if (!stream.is_open())
        {
            std::cerr << "Failed to open Shader file: " << relativePath.c_str() << std::endl;
            return std::string{};
        }

        std::stringstream buffer;
        buffer << stream.rdbuf();
        
        return buffer.str();
    }

    std::shared_ptr<ShaderProgram> ResourceManager::LoadShaders(
        const std::string& shaderName,
        const std::string& vertexShaderPath,
        const std::string& fragmentShaderPath)
    {
        std::string vertexShaderCode = GetShaderCode(vertexShaderPath);
        if (vertexShaderCode.empty())
        {
            std::cerr << "VERTEX SHADER load error!" << std::endl;
            return nullptr;
        }

        std::string fragmentShaderCode = GetShaderCode(fragmentShaderPath);
        if (fragmentShaderCode.empty())
        {
            std::cerr << "FRAGMENT SHADER load error!" << std::endl;
            return nullptr;
        }

        std::shared_ptr<ShaderProgram>& shader =  shaderPrograms.emplace(shaderName, std::make_shared<ShaderProgram>(vertexShaderCode, fragmentShaderCode)).first->second;
        if (!shader -> IsCompiled())
        {
            std::cerr << "Can't load shader program for:\n"
            << "Vertex Shader: " << vertexShaderPath << std::endl
            << "Fragment Shader: " << fragmentShaderPath
            << std::endl;
            
            return nullptr;
        }
        
        return shader;
    }

    std::shared_ptr<ShaderProgram> ResourceManager::GetShaderProgram(const std::string& shaderName)
    {
        const ShaderProgramsMap::const_iterator iterator = shaderPrograms.find(shaderName);
        if (iterator == shaderPrograms.end())
        {
            std::cerr << "Can't find shader program: " << shaderName << std::endl;
            return nullptr;
        }

        return iterator -> second;
    }



}
