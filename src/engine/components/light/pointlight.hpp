#pragma once

#include "light.hpp"

namespace Engine
{
  namespace Components
  {
    class PointLight : public Light
    {
      public:
        typedef std::shared_ptr<PointLight> PointLightPtr;

      public:
        static constexpr float INITIAL_FOV = 45.0f;

        PointLightPtr
        static inline
        create()
        {
          return std::make_shared<PointLight>();
        }

      public:
        PointLight();
        ~PointLight();
    };
  }
}
