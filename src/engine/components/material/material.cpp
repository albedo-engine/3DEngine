#include <components/renderer/renderer.hpp>
#include "material.hpp"

namespace Engine
{
  namespace Components
  {
    Material::Material()
            : shader_(Rendering::Shader::createFromStrings(
            get_vertex_shader(),
            get_fragment_shader()))
    {
      shader_.compile();
    }

    Material::~Material()
    {
    }

    const Rendering::Shader
    Material::get_shader() const
    {
      return shader_;
    }


    const GLchar*
    Material::get_vertex_shader()
    {
      return "#version 330 core\n"
              "layout (location = 0) in vec3 position;\n"
              "uniform mat4 transform;\n"
              "void main()\n"
              "{\n"
              "gl_Position = transform * vec4(position, 1.0);\n"
              "}\0";
    }

    const GLchar*
    Material::get_fragment_shader()
    {
      return "#version 330 core\n"
              "out vec4 color;\n"
              "void main()\n"
              "{\n"
              "color = vec4(1.0f, 0.8f, 0.2f, 1.0f);\n"
              "}\n\0";
    }

    bool
    Material::unique()
    {
      return true;
    }

  } // namespace Components
} // namespace Engine
