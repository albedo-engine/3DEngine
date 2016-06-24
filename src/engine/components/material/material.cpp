#include <components/renderer/renderer.hpp>
#include "material.hpp"

namespace Engine
{
  namespace Components
  {
    int Material::ID = 0;

    Material::Material()
            : shader_(Rendering::Shader::createFromStrings(
            get_vertex_shader(),
            get_fragment_shader()))
    {
      shader_.compile();

      // Updates the global material ID
      material_id_ = ID++;
    }

    Material::~Material()
    {
    }

    const Rendering::Shader
    Material::get_shader() const
    {
      return shader_;
    }

    const int&
    Material::get_material_id() const
    {
      return material_id_;
    }

    const GLchar*
    Material::get_vertex_shader()
    {
      return "#version 330 core\n"
              "layout (location = 0) in vec3 position;\n"
              "uniform mat4 model;\n"
              "uniform mat4 view;\n"
              "uniform mat4 projection;\n"
              "void main()\n"
              "{\n"
              "gl_Position = projection * view * model * vec4(position, 1.0);\n"
              "}\0";
    }

    const GLchar*
    Material::get_fragment_shader()
    {
      return "#version 330 core\n"
              "out vec4 color;\n"
              "void main()\n"
              "{\n"
              "color = vec4(1.0f, 0.8f, 0.3f, 1.0f);\n"
              "}\n\0";
    }

    bool
    Material::unique()
    {
      return true;
    }

  } // namespace Components
} // namespace Engine
