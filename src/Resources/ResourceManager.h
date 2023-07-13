#pragma once
#include <map>
#include <memory>
#include <string>

#include "../Renderer/ShaderProgram.h"

namespace Renderer
{
    class ResourceManager
    {
    public:
        ResourceManager(const std::string& executablePath);
        ~ResourceManager() = default;

        ResourceManager(const ResourceManager&) = delete;
        ResourceManager& operator=(const ResourceManager&) = delete;
        ResourceManager& operator=(ResourceManager&&) = delete;
        ResourceManager(ResourceManager&&) = delete;

        std::shared_ptr<ShaderProgram> LoadShaders(
            const std::string& shaderName,
            const std::string& vertexShaderPath,
            const std::string& fragmentShaderPath
            );

        std::shared_ptr<ShaderProgram> GetShaderProgram(const std::string& shaderName);
    
    private:
        typedef std::map<const std::string, std::shared_ptr<ShaderProgram>> ShaderProgramsMap;
        ShaderProgramsMap shaderPrograms;
        
        std::string path;

        std::string GetShaderCode(const std::string& relativePath) const;
    };
}