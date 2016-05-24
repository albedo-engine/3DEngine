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
        create()
        {
          return std::make_shared<PerspectiveCamera>();
        }

        PerspectiveCameraPtr
        static inline
        create(float fov)
        {
          return std::make_shared<PerspectiveCamera>(fov);
        }

      public:
        PerspectiveCamera();
        PerspectiveCamera(float fov);
        ~PerspectiveCamera();

        void update() override;

        const float& get_fov() const;
        void set_fov(const float& fov);

      private:
        float fov_;
    };
  }
}
