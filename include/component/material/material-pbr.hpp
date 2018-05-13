#pragma once

#include <utils/headers/common.hpp>

#include <components/material/material.hpp>
#include <rendering/texture-2d.hpp>

namespace Engine
{
  namespace Components
  {
    class MaterialPBR : public Material
    {
      public:
        typedef std::shared_ptr<MaterialPBR>        MaterialPBRPtr;
        typedef Rendering::Texture2D::Texture2DPtr  Texture2DPtr;

      public:
        MaterialPBRPtr
        static inline
        create()
        {
          return MaterialPBRPtr(new MaterialPBR());
        }

      private:
        MaterialPBR();

      public:
        MaterialPBRPtr
        setColorFactor(const glm::vec4 colorFactor);

        MaterialPBRPtr
        setAlbedo(const Texture2DPtr& texture);
    };
  } // namespace Component
} // namespace Engine
