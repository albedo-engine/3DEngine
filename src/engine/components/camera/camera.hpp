#pragma once

#include <utils/headers/common.hpp>
#include <components/component.hpp>

namespace Engine
{
  namespace Components
  {
    class Camera : public Component
    {
      public:
        typedef std::shared_ptr<Camera> CameraPtr;

      public:
        Camera();
        virtual ~Camera();

        virtual void update() = 0;

        const glm::mat4& get_projection_matrix() const;

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

