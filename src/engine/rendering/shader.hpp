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
          private:
            Shader(const GLchar* vertexShader, const GLchar* fragmentShader);

          public:

            static Shader
            createFromStrings(const GLchar* vertexShader, const GLchar* fragmentShader);

            static Shader
            createFromFiles(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath);


            bool compile();
            const GLchar* get_compilation_info();

            void use_shader();


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
