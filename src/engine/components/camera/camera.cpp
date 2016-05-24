#include "camera.hpp"

namespace Engine
{
  namespace Components
  {
    Camera::Camera()
            : viewport_width_{0.0f}
            , viewport_height_{0.0f}
            , far_{100.0f}
            , near_{1.0f}
    { }

    Camera::~Camera()
    { }

    const glm::mat4&
    Camera::get_projection_matrix() const
    {
      return projection_matrix_;
    }

  } // Namespace Components
} // Namespace Engine