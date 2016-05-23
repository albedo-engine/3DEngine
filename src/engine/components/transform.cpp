#include "transform.hpp"

namespace Engine
{
  namespace Components
  {
    Transform::Transform()
    { }

    Transform::Transform(glm::vec3 position)
    {
      this->translate(position);
    }

    Transform::Transform(glm::vec3 scale, glm::vec3 rot_axis, float angle)
    {
      world_matrix_ = glm::rotate(world_matrix_, glm::radians(angle), rot_axis)
                      * glm::scale(world_matrix_, scale);
    }

    Transform::Transform(glm::vec3 scale, glm::vec3 position, glm::vec3 rot_axis, float angle)
    {
      this->scale_rot_translate(scale, position, rot_axis, angle);
    }

    void
    Transform::translate(glm::vec3 position)
    {
      world_matrix_ = glm::translate(world_matrix_, position);
    }

    void
    Transform::translate(double x, double y, double z)
    {
      this->translate(glm::vec3(x, y, z));
    }

    void
    Transform::rotate(float angle, glm::vec3 rot_axis)
    {
      world_matrix_ = glm::rotate(world_matrix_, glm::radians(angle), rot_axis);
    }

    void
    Transform::rotate(float angle, double xaxis, double yaxis, double zaxis)
    {
      this->rotate(angle, glm::vec3(xaxis, yaxis, zaxis));
    }

    void
    Transform::scale(glm::vec3 factor)
    {
      world_matrix_ = glm::scale(world_matrix_, factor);
    }

    void
    Transform::scale(double xaxis, double yaxis, double zaxis)
    {
      this->scale(glm::vec3(xaxis, yaxis, zaxis));
    }

    void
    Transform::scale_rot_translate(glm::vec3 scale, glm::vec3 position,
                                   glm::vec3 rot_axis, float angle)
    {
      world_matrix_ = glm::translate(world_matrix_, position)
                      * glm::rotate(world_matrix_, glm::radians(angle), rot_axis)
                      * glm::scale(world_matrix_, scale);
    }

  } // namespace Component
} // namespace Engine
