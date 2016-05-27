#include "shader.hpp"

namespace Engine
{
    namespace Rendering
    {
        Shader::Shader(const GLchar* vertexShader, const GLchar* fragmentShader)
                : vertexShader_(vertexShader)
                , fragmentShader_(fragmentShader)
        {
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
            fragment = glCreateShader(GL_VERTEX_SHADER);
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

        const GLchar*
        Shader::getCompilationInfo()
        {
            return compileInfo_;
        }

        void
        Shader::use_shader()
        {
            glUseProgram(program_);
        }
    }
}
