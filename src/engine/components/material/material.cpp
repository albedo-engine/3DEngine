#include <components/renderer/renderer.hpp>
#include "material.hpp"

namespace Engine
{
  namespace Components
  {
    GLuint Material::ID = 0;

    Material::Material()
    {
      this->store_ = Data::Store::create();
      // Updates the global material ID
      materialId_ = ID++;
    }

    Material::~Material()
    { }

    void
    Material::sendUniforms()
    {
      shader_->sendStoreData(store_);
    }

    void
    Material::setShader(const Rendering::Shader::ShaderPtr& shader)
    {
      shader_ = shader;
    }

    const Rendering::Shader::ShaderPtr&
    Material::getShader() const
    {
      return shader_;
    }

    const GLuint&
    Material::getMaterialId() const
    {
      return materialId_;
    }

    const Data::Store::StorePtr&
    Material::getStore() const
    {
      return store_;
    }

    bool
    Material::unique()
    {
      return true;
    }

  } // namespace Components
} // namespace Engine
