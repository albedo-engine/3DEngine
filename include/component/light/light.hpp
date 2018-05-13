#pragma once

#include <utils/headers/common.hpp>

#include <component/component-manager.hpp>
#include <component/component.hpp>
#include <component/transform/transform.hpp>

#include <data/store.hpp>

namespace Engine
{
  namespace Components
  {
    class Light : public Component, public std::enable_shared_from_this<Light>
    {
      public:
        typedef std::shared_ptr<Light> LightPtr;

      public:
        Light();

      public:
        virtual ~Light() = 0;

      public:
        bool
        unique() override;

        const glm::vec3&
        getColor() const;

        void
        setColor(const glm::vec3 color);

      private:
        Data::Store::StorePtr store_;

    };
  } // Namespace Component
} // Namespace Engine
