#include "perspective-camera.hpp"

namespace Engine
{
  namespace Components
  {
    PerspectiveCamera::PerspectiveCamera(float viewport_width,
                                         float viewport_height)
            : Camera(viewport_width, viewport_height)
            , fov_{INITIAL_FOV}
    { update(); }

    PerspectiveCamera::PerspectiveCamera(float viewport_width,
                                         float viewport_height, float fov)
            : Camera(viewport_width, viewport_height)
            , fov_{fov}
    { update(); }

    PerspectiveCamera::~PerspectiveCamera()
    { }

    void
    PerspectiveCamera::update()
    {
      projection_matrix_ = glm::perspective
              (
                      fov_,
                      (GLfloat)viewport_width_ / (GLfloat)viewport_height_,
                      near_, far_
              );
    }

    const float&
    PerspectiveCamera::get_fov() const
    {
      return fov_;
    }

    void
    PerspectiveCamera::set_fov(const float& fov)
    {
      fov_ = fov;
    }
  } // Namespace Components
} // Namespace Engine

