#pragma once

#include "../../utils/headers/common.hpp"

namespace Engine
{
    namespace Rendering
    {
        class Shader
        {
          public:
            Shader(const GLchar* vertexShader, const GLchar* fragmentShader);

            bool compile();
            const GLchar* getCompilationInfo();

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
