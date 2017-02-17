#pragma once

#include "camera.hpp"

namespace Engine
{
  namespace Components
  {
    class PerspectiveCamera : public Camera
    {
      public:
        typedef std::shared_ptr<PerspectiveCamera> PerspectiveCameraPtr;

      public:
        static constexpr float INITIAL_FOV = 45.0f;

        PerspectiveCameraPtr
        static inline
        create(float viewportWidth, float viewportHeight)
        {
          return PerspectiveCameraPtr(new PerspectiveCamera(viewportWidth, viewportHeight));
        }

        PerspectiveCameraPtr
        static inline
        create(float viewportWidth, float viewportHeight, float fov)
        {
          return PerspectiveCameraPtr(new PerspectiveCamera(viewportWidth, viewportHeight, fov));
        }

      public:
        ~PerspectiveCamera();

      public:
        void
        update() override;

      public:
        const float&
        getFov() const;

        void
        setFov(const float& fov);

      private:
        PerspectiveCamera(float viewport_width, float viewport_height);
        PerspectiveCamera(float viewport_width, float viewport_height, float fov);

      private:
        float fov_;
    };
  }
}
