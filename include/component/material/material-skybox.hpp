#pragma once

#include "components/material/material.hpp"

#include <rendering/texture-cubemap.hpp>

namespace Engine
{
  namespace Components
  {
    class MaterialSkybox : public Material
    {
      public:
        typedef std::shared_ptr<MaterialSkybox>               MaterialSkyboxPtr;

      private:
        typedef Rendering::TextureCubemap::TextureCubemapPtr  TextureCubemapPtr;

      public:
        MaterialSkyboxPtr
        static inline
        create()
        {
          return MaterialSkyboxPtr(new MaterialSkybox);
        }

      public:
        void
        setCubemap(const TextureCubemapPtr& cubemap);

      private:
        MaterialSkybox();

      private:
        TextureCubemapPtr cubemap_;
    };
  } // namespace Component
} // namespace Engine
