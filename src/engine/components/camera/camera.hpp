#pragma once

namespace Engine
{
  namespace Components
  {
    class Camera : public Component
    {
      public:
        typedef std::shared_ptr<Camera> CameraPtr;

      public:
        virtual ~Camera() = 0;

        virtual void update() = 0;

      protected:
        float     viewport_width_;
        float     viewport_height_;
        float     far_;
        float     near_;
        glm::mat4 projection_matrix_;

    };
  } // Namespace Component
} // Namespace Engine

