#include "perspective-camera.hpp"

namespace Engine
{
  namespace Components
  {
    PerspectiveCamera::PerspectiveCamera()
                      : Camera()
                      , fov_{INITIAL_FOV}
    { }

    PerspectiveCamera::PerspectiveCamera(float fov)
                      : Camera()
                      , fov_{fov}
    { }

    override void
    PerspectiveCamera::update()
    {
      projection_matrix_ = glm::perspective
                           (
                             fov_,
                             (GLfloat)viewport_width_/(GLfloat)viewport_height_,
                             near_, far_
                           );
    }

    const float&
    PerspectiveCamera::get_fov() const
    {
      return fov_;
    }

    void
    PerspectiveCamera::set_fov(const float& fov) const
    {
      fov_ = fov;
    }
  } // Namespace Components
} // Namespace Engine

