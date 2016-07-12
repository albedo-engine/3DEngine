#pragma once

#include <fstream>
#include <sstream>
#include <utils/headers/common.hpp>

namespace Engine
{
  namespace Rendering
  {
    class Shader
    {
      public:
        typedef std::shared_ptr<Shader> ShaderPtr;

      public:

        static ShaderPtr
                createFromStrings(const GLchar* vertexShader,
                                  const GLchar* fragmentShader);

        static ShaderPtr
                createFromFiles(const GLchar* vertexShaderPath,
                                const GLchar* fragmentShaderPath);

      public:
        Shader(const GLchar* vertexShader, const GLchar* fragmentShader);

      public:
        bool compile();
        const GLchar* get_compilation_info();

        void use_shader() const;

        const GLuint& get_program() const;

      private:
        bool has_compiled(GLuint shader);

      private:
        const GLchar* vertexShader_;
        const GLchar* fragmentShader_;

        GLuint program_;

        GLchar compileInfo_[512];
    };
  } // namespace Rendering
} // namespace Engine
