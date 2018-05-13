#pragma once

#include <lib/glm/glm/glm.hpp>
#include <component/component.hpp>

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
        bool
        unique() override;

        virtual void
        update() = 0;

      public:
        const glm::mat4&
        getProjection() const;

        const glm::mat4&
        getView();

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
