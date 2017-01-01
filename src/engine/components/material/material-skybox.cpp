#include "material-skybox.hpp"

namespace Engine
{
  namespace Components
  {
    void
    MaterialSkybox::setCubemap(MaterialSkybox::TextureCubemapPtr cubemap)
    {
      store_.set<MaterialSkybox::TextureCubemapPtr>("uCubemap", cubemap);
    }
  } // namespace Component
} // namespace Engine
