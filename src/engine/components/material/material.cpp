#include <components/renderer/renderer.hpp>
#include "material.hpp"

namespace Engine
{
  namespace Components
  {
    GLuint Material::ID = 0;

    Material::Material()
    {
      // Updates the global material ID
      material_id_ = ID++;
    }

    Material::~Material()
    {
    }

    void
    Material::set_shader(Rendering::Shader::ShaderPtr shader)
    {
      shader_ = shader;
    }

    const Rendering::Shader::ShaderPtr
    Material::get_shader() const
    {
      return shader_;
    }

    const GLuint&
    Material::get_material_id() const
    {
      return material_id_;
    }

    bool
    Material::unique()
    {
      return true;
    }

  } // namespace Components
} // namespace Engine
