#pragma once

namespace Engine
{
  namespace Components
  {
    class PerspectiveCamera : public Camera
    {
      public:
        typedef std::shared_ptr<PerspectiveCamera> PerspectiveCameraPtr;

      public:
        static const float INITIAL_FOV = 45.0f;

      public:
        PerspectiveCamera();
        PerspectiveCamera(float fov);

        override void update();

        const float& get_fov() const;
        void set_fov(const float& fov);

      private:
        float     fov_;
    };
  }
}
