#pragma once

#include <utils/headers/common.hpp>
#include <components/component.hpp>
#include <components/transform/transform.hpp>

namespace Engine
{
  namespace Components
  {
    class Light : public Component
    {
      public:
        typedef std::shared_ptr<Light> LightPtr;

      public:
        Light();

      public:
        virtual ~Light() = 0;

      public:
        bool unique() override;

        const glm::vec3& get_color() const;
        void set_color(glm::vec3 color);

      private:
        glm::vec3 color_;

    };
  } // Namespace Component
} // Namespace Engine

