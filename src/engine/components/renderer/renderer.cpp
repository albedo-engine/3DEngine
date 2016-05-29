#include "renderer.hpp"

namespace Engine
{
  namespace Components
  {
    Renderer::Renderer()
      : quadShader_(Rendering::Shader::createFromStrings(
            get_quad_vertex_shader(), get_quad_fragment_shader()))
    {
      if (!quadShader_.compile())
        throw std::runtime_error("Quad shader "
                                 + std::string(quadShader_.get_compilation_info()));
    }

    bool
    Renderer::unique()
    {
      return false;
    }

    const GLchar*
    Renderer::get_quad_vertex_shader()
    {
      return "#version 330 core\n"
              "layout (location = 0) in vec2 position;\n"
              "layout (location = 1) in vec2 texCoords;\n"
              "\n"
              "out vec2 TexCoords;\n"
              "\n"
              "void main()\n"
              "{\n"
              "    gl_Position = vec4(position.x, position.y, 0.0f, 1.0f); \n"
              "    TexCoords = texCoords;\n"
              "}\n\0";
    }

    const GLchar*
    Renderer::get_quad_fragment_shader()
    {
      return "#version 330 core\n"
              "in vec2 TexCoords;\n"
              "out vec4 color;\n"
              "\n"
              "uniform sampler2D screenTexture;\n"
              "\n"
              "void main()\n"
              "{ \n"
              "    color = texture(screenTexture, TexCoords);\n"
              "}\n\0";
    }

  } // namespace Components
} // namespace Engine
