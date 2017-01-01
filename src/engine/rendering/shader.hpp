#pragma once

#include <fstream>
#include <sstream>
#include <unordered_map>
#include <initializer_list>
#include <utils/headers/common.hpp>

#include <rendering/texture-2d.hpp>
#include <rendering/texture-cubemap.hpp>
#include <data/store.hpp>

namespace Engine
{
  namespace Rendering
  {
    class Shader : public std::enable_shared_from_this<Shader>
    {
      public:
        typedef std::shared_ptr<Shader>                      ShaderPtr;
        typedef Rendering::Texture2D::Texture2DPtr           Texture2DPtr;
        typedef Rendering::TextureCubemap::TextureCubemapPtr TextureCubemapPtr;
        typedef std::unordered_map<std::string, std::string> UniformsList;
        typedef std::unordered_map<std::string, int>         TextureUnitMap;

      public:
        static
        ShaderPtr
        create(const GLchar* vxShaderPath, const GLchar* fgShaderPath)
        {
          return std::make_shared<Shader>(vxShaderPath, fgShaderPath);
        }

      public:
        Shader(const GLchar* vertexShader, const GLchar* fragmentShader);

        static ShaderPtr
        createFromFiles(const GLchar* vertexShaderPath,
                        const GLchar* fragmentShaderPath);

      public:
        bool
        compile();

        void
        sendStoreData(Data::Store& store);

        void
        useShader() const;

      public:
        ShaderPtr
        addUniform(std::pair<std::string, std::string> value);

        const GLchar*
        getCompilationInfo();

        const GLuint&
        getProgram() const;

      private:
        bool
        hasCompiled(GLuint shader);

        void
        buildTextureUnit();

      private:
        void
        setUniform(const std::string& uniform, const int* value);

        void
        setUniform(const std::string& uniform, const float* value);

        void
        setUniform(const std::string& uniform, const glm::vec2* value);

        void
        setUniform(const std::string& uniform, const glm::vec3* value);

        void
        setUniform(const std::string& uniform, const glm::vec4* value);

        void
        setUniform(const std::string& uniform, const glm::mat4* value);

      private:
        const GLchar* vertexShader_;
        const GLchar* fragmentShader_;

        UniformsList   uniforms_;
        TextureUnitMap textureUnitMap_;

        GLuint program_;
        GLchar compileInfo_[512];

        GLboolean depthMask_;
    };
  } // namespace Rendering
} // namespace Engine
