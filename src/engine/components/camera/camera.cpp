#include "camera.hpp"

namespace Engine
{
  namespace Components
  {
    Camera::Camera(float viewport_width, float viewport_height)
            : viewport_width_{viewport_width}
            , viewport_height_{viewport_height}
            , far_{100.0f}
            , near_{1.0f}
    { }

    Camera::~Camera()
    { }

    bool
    Camera::unique()
    {
      return false;
    }

    const glm::mat4&
    Camera::get_projection_matrix() const
    {
      return projection_matrix_;
    }

  } // Namespace Components
} // Namespace Engine