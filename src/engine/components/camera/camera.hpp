#pragma once

#include <utils/headers/common.hpp>
#include <components/component.hpp>
#include <components/transform/transform.hpp>

namespace Engine
{
  namespace Components
  {
    class Camera : public Component
    {
      public:
        typedef std::shared_ptr<Camera> CameraPtr;

      public:
        Camera(float viewport_width, float viewport_height);

      public:
        virtual ~Camera();

      public:
        bool unique() override;
        virtual void update() = 0;

      public:
        const glm::mat4& get_projection_matrix() const;
        const glm::mat4& get_view_matrix();

      protected:
        float     viewport_width_;
        float     viewport_height_;
        float     far_;
        float     near_;
        glm::mat4 view_matrix_;
        glm::mat4 projection_matrix_;

    };
  } // Namespace Component
} // Namespace Engine

