#include "shader.hpp"
#include "texture-2d.hpp"

namespace Engine
{
  namespace Rendering
  {

    Shader::Shader(const GLchar* vertexShader, const GLchar* fragmentShader)
      : vertexShader_(vertexShader)
      , fragmentShader_(fragmentShader)
      , depthMask_(GL_TRUE)
    {}

    Shader::ShaderPtr
    Shader::createFromFiles(const GLchar* vertexShaderPath,
                            const GLchar* fragmentShaderPath)
    {
      std::string vertexShader;
      std::string fragmentShader;

      std::ifstream vertexShaderFStream(vertexShaderPath, std::ifstream::in);
      if (vertexShaderFStream)
      {
        std::stringstream vertexShaderSStream;
        vertexShaderSStream << vertexShaderFStream.rdbuf();
        vertexShaderFStream.close();
        vertexShader = vertexShaderSStream.str();
      }
      else
        throw std::invalid_argument("Vertex shader file cannot be opened");

      std::ifstream fragmentShaderFStream(fragmentShaderPath,
                                          std::ifstream::in);
      if (fragmentShaderFStream)
      {
        std::stringstream fragmentShaderSStream;
        fragmentShaderSStream << fragmentShaderFStream.rdbuf();
        fragmentShaderFStream.close();
        fragmentShader = fragmentShaderSStream.str();
      }
      else
        throw std::invalid_argument("Fragment shader file cannot be opened");

      return std::make_shared<Shader>(vertexShader.c_str(),
                                      fragmentShader.c_str());
    }

    bool
    Shader::compile()
    {
      GLuint vertex;
      GLuint fragment;

      // Vertex Shader
      vertex = glCreateShader(GL_VERTEX_SHADER);
      glShaderSource(vertex, 1, &vertexShader_, NULL);
      glCompileShader(vertex);
      if (!has_compiled(vertex))
        return false;

      // Fragment Shader
      fragment = glCreateShader(GL_FRAGMENT_SHADER);
      glShaderSource(fragment, 1, &fragmentShader_, NULL);
      glCompileShader(fragment);
      if (!has_compiled(fragment))
        return false;

      // Link shaders
      program_ = glCreateProgram();
      glAttachShader(program_, vertex);
      glAttachShader(program_, fragment);
      glLinkProgram(program_);

      // Check for linking errors
      GLint success;
      glGetProgramiv(program_, GL_LINK_STATUS, &success);
      if (!success)
      {
        glGetProgramInfoLog(program_, 512, NULL, compileInfo_);
        return false;
      };

      // Delete shaders
      glDeleteShader(vertex);
      glDeleteShader(fragment);

      return true;
    }

    void
    Shader::sendStoreData(Data::Store& store)
    {
      auto& materialUniforms = store.getAttributesMap();

      for (auto& attr : uniforms_)
      {
        auto& uniformName = attr.first;
        auto& type        = attr.second;

        if (type == "int")
          this->setUniform(uniformName, store.get<int>(uniformName));
        else if (type == "float")
          this->setUniform(uniformName, store.get<float>(uniformName));
        else if (type == "vec2")
          this->setUniform(uniformName, store.get<glm::vec2>(uniformName));
        else if (type == "vec3")
          this->setUniform(uniformName, store.get<glm::vec3>(uniformName));
        else if (type == "vec4")
          this->setUniform(uniformName, store.get<glm::vec4>(uniformName));
        else if (type == "mat4")
          this->setUniform(uniformName, store.get<glm::mat4>(uniformName));
        else if (type == "sampler2D")
        {
          auto texture2D = store.get<Shader::Texture2DPtr>(uniformName);
          if (texture2D == nullptr)
            continue;

          glActiveTexture(GL_TEXTURE0 + textureUnitMap_[uniformName]);
          glBindTexture(GL_TEXTURE_2D, (*texture2D)->getTextureId());
          this->setUniform(uniformName, &textureUnitMap_[uniformName]);
        }
        else if (type == "samplerCube")
        {
          auto cubemap = store.get<Shader::TextureCubemapPtr>(uniformName);
          if (cubemap == nullptr)
            continue;

          glActiveTexture(GL_TEXTURE0 + textureUnitMap_[uniformName]);
          glBindTexture(GL_TEXTURE_CUBE_MAP, (*cubemap)->getTextureId());
          this->setUniform(uniformName, &textureUnitMap_[uniformName]);
        }
      }
    }

    void
    Shader::use_shader() const
    {
      // Enable / Disable depth testing
      glDepthMask(depthMask_);
      glUseProgram(program_);
    }

    Shader::ShaderPtr
    Shader::addUniform(std::pair<std::string, std::string> value)
    {
      uniforms_[value.first] = value.second;
      if (value.second == "sampler2D" || value.second == "samplerCube")
        this->buildTextureUnit();

      return std::static_pointer_cast<Shader>(shared_from_this());
    }

    void
    Shader::setDepthMask(GLboolean mask)
    {
      depthMask_ = mask;
    }

    const GLchar*
    Shader::get_compilation_info()
    {
      return compileInfo_;
    }

    const GLuint&
    Shader::get_program() const
    {
      return program_;
    }

    void
    Shader::setUniform(const std::string& uniformName, const int* value)
    {
      if (value == nullptr)
        return;

      GLint location = glGetUniformLocation(program_, uniformName.c_str());
      glUniform1i(location, *value);
    }

    void
    Shader::setUniform(const std::string& uniformName, const float* value)
    {
      if (value == nullptr)
        return;

      GLint location = glGetUniformLocation(program_, uniformName.c_str());
      glUniform1f(location, *value);
    }

    void
    Shader::setUniform(const std::string& uniformName, const glm::vec2* value)
    {
      if (value == nullptr)
        return;

      GLint location = glGetUniformLocation(program_, uniformName.c_str());
      glUniform2fv(location, 1, &(*value)[0]);
    }

    void
    Shader::setUniform(const std::string& uniformName, const glm::vec3* value)
    {
      if (value == nullptr)
        return;

      GLint location = glGetUniformLocation(program_, uniformName.c_str());
      glUniform3fv(location, 1, &(*value)[0]);
    }

    void
    Shader::setUniform(const std::string& uniformName, const glm::vec4* value)
    {
      if (value == nullptr)
        return;

      GLint location = glGetUniformLocation(program_, uniformName.c_str());
      glUniform4fv(location, 1, &(*value)[0]);
    }

    void
    Shader::setUniform(const std::string& uniformName, const glm::mat4* value)
    {
      if (value == nullptr)
        return;

      GLint location = glGetUniformLocation(program_, uniformName.c_str());
      glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(*value));
    }

    bool
    Shader::has_compiled(GLuint shader)
    {
      GLint success;
      glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
      if (!success)
      {
        glGetShaderInfoLog(shader, 512, NULL, compileInfo_);
        return false;
      }
      return true;
    }

    void
    Shader::buildTextureUnit()
    {
      int unit = 0;
      for (auto& it : uniforms_)
      {
        if (it.second == "sampler2D")
          textureUnitMap_[it.first] = unit++;
      }
    }
  }
}
