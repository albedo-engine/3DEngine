#include "material-skybox.hpp"

namespace Engine
{
  namespace Components
  {
    MaterialSkybox::MaterialSkybox()
    {}

    void
    MaterialSkybox::setCubemap(const MaterialSkybox::TextureCubemapPtr& cubemap)
    {
      store_->set<MaterialSkybox::TextureCubemapPtr>("uCubemap", cubemap);
    }
  } // namespace Component
} // namespace Engine
