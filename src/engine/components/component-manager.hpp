#pragma once

#include <vector>
#include <memory>

#include <data/singleton.hpp>

#include <components/material/material.hpp>
#include <components/light/light.hpp>

namespace Engine
{
  namespace Components
  {
    class Light;

    class Material;

    class ComponentManager : public Singleton<ComponentManager>
    {
      public:
        typedef std::vector<std::shared_ptr<Light>>    LightsVector;
        typedef std::vector<std::shared_ptr<Material>> MaterialVector;

      public:
        inline
        LightsVector&
        getLights()
        {
          return lightsVector_;
        }

        inline
        MaterialVector&
        getMaterials()
        {
          return materialsVector_;
        }

      private:
        LightsVector   lightsVector_;
        MaterialVector materialsVector_;
    };
  } // namespace Components
} // namespace Engine
