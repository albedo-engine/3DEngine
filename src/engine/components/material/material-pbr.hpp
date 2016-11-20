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
          return std::make_shared<MaterialPBR>();
        }

      public:
        /*MaterialPBRPtr&
        setBaseColor();*/

        MaterialPBRPtr
        setColorFactor(glm::vec4 colorFactor);

        MaterialPBRPtr
        setAlbedo(Texture2DPtr texture);

        /*MaterialPBRPtr&
        setRoughnessFactor(float roughnessFactor);*/
    };
  } // namespace Component
} // namespace Engine