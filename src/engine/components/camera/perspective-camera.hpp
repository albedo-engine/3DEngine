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
        create(float viewport_width, float viewport_height)
        {
          return std::make_shared<PerspectiveCamera>(viewport_width,
                                                     viewport_height);
        }

        PerspectiveCameraPtr
        static inline
        create(float viewport_width, float viewport_height, float fov)
        {
          return std::make_shared<PerspectiveCamera>(viewport_width,
                                                     viewport_height, fov);
        }

      public:
        PerspectiveCamera(float viewport_width, float viewport_height);
        PerspectiveCamera(float viewport_width, float viewport_height,
                          float fov);
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
        float fov_;
    };
  }
}
