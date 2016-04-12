#include "transform.hpp"

namespace Engine
{
  namespace Components
  {
    Transform::Transform()
    { }

    Transform::Transform(glm::vec3 position)
    {
      world_matrix_ = glm::translate(world_matrix_, position);
    }

    Transform::Transform(glm::vec3 scale, glm::vec3 rot_axis, float angle)
    {
      world_matrix_ = glm::scale(world_matrix_, scale);
      world_matrix_ = glm::rotate(world_matrix_, glm::radians(angle), rot_axis);
    }

    Transform::Transform(glm::vec3 scale, glm::vec3 position, glm::vec3 rot_axis, float angle)
    {
      world_matrix_ = glm::scale(world_matrix_, scale);
      world_matrix_ = glm::rotate(world_matrix_, glm::radians(angle), rot_axis);
      world_matrix_ = glm::translate(world_matrix_, position);
    }

    void
    Transform::translate(glm::vec3 position)
    {
      world_matrix_ = glm::translate(world_matrix_, position);
    }

    void
    Transform::translate(double x, double y, double z)
    { }

    void
    Transform::rotate(double angle, glm::vec3 axis)
    { }

    void
    Transform::rotate(double angle, double xaxis, double yaxis, double zaxis)
    { }

    void
    Transform::scale(glm::vec3 factor)
    { }

    void
    Transform::scale(double xaxis, double yaxis, double zaxis)
    { }

  } // namespace Component
} // namespace Engine
