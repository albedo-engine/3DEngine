#pragma once

#include <component/light/light.hpp>

namespace Engine
{
  namespace Components
  {
    class PointLight : public Light
    {
      public:
        typedef std::shared_ptr<PointLight> PointLightPtr;

      public:
        PointLightPtr
        static inline
        create()
        {
          auto ptr = PointLightPtr(new PointLight);
          ComponentManager::instance()->getLights().push_back(ptr);

          return ptr;
        }

      public:
        ~PointLight();

      private:
        PointLight();
    };
  }
}
