#include "material-pbr.hpp"

namespace Engine
{
  namespace Components
  {
    MaterialPBR::MaterialPBR()
    {}

    MaterialPBR::MaterialPBRPtr
    MaterialPBR::setColorFactor(const glm::vec4 colorFactor)
    {
      store_->set<glm::vec4>("uAlbedoFactor", colorFactor);
      return std::static_pointer_cast<MaterialPBR>(shared_from_this());
    }

    MaterialPBR::MaterialPBRPtr
    MaterialPBR::setAlbedo(const Texture2DPtr& texture)
    {
      store_->set<MaterialPBR::Texture2DPtr>("uAlbedoMap", texture);
      return std::static_pointer_cast<MaterialPBR>(shared_from_this());
    }

  } // namespace Component
} // namespace Engine
