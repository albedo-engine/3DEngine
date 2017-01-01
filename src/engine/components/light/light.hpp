#pragma once

#include <utils/headers/common.hpp>

#include <components/component-manager.hpp>
#include <components/component.hpp>
#include <components/transform/transform.hpp>

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
        setColor(glm::vec3 color);

      private:
        Data::Store store_;

    };
  } // Namespace Component
} // Namespace Engine
