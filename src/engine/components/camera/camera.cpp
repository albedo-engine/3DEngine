#include "camera.hpp"

namespace Engine
{
  namespace Components
  {
    Camera::Camera(float viewport_width, float viewport_height)
            : viewport_width_{viewport_width}
            , viewport_height_{viewport_height}
            , far_{500.0f}
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

    const glm::mat4&
    Camera::get_view_matrix()
    {
      if (get_target() != nullptr && get_target()->component<Transform>() == nullptr)
        throw new std::logic_error("A Camera component should be linked to a Transform component.");

      auto transform = get_target()->component<Transform>();

      auto position = transform->get_world_position();
      auto direction = transform->get_direction();
      auto up = transform->get_up();

      view_matrix_ = glm::lookAt(position, position + direction, up);

      return view_matrix_;
    }

  } // Namespace Components
} // Namespace Engine