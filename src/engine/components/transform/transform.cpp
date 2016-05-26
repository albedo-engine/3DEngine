#include "transform.hpp"

namespace Engine
{
  namespace Components
  {
    /*Transform::Transform()
    { }

    Transform::Transform(glm::vec3 position)
    {
      this->translate(position);
    }

    Transform::Transform(glm::vec3 scale, glm::vec3 rot_axis, float angle)
    {
      local_matrix_ = glm::rotate(local_matrix_, glm::radians(angle), rot_axis)
                      * glm::scale(local_matrix_, scale);
    }

    Transform::Transform(glm::vec3 scale, glm::vec3 position, glm::vec3 rot_axis, float angle)
    {
      this->scale_rot_translate(scale, position, rot_axis, angle);
    }

    void
    Transform::translate(glm::vec3 position)
    {
      local_matrix_ = glm::translate(local_matrix_, position);
    }

    void
    Transform::translate(double x, double y, double z)
    {
      this->translate(glm::vec3(x, y, z));
    }

    void
    Transform::rotate(float angle, glm::vec3 rot_axis)
    {
      local_matrix_ = glm::rotate(local_matrix_, glm::radians(angle), rot_axis);
    }

    void
    Transform::rotate(float angle, double xaxis, double yaxis, double zaxis)
    {
      this->rotate(angle, glm::vec3(xaxis, yaxis, zaxis));
    }

    void
    Transform::scale(glm::vec3 factor)
    {
      local_matrix_ = glm::scale(local_matrix_, factor);
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
      local_matrix_ = glm::translate(local_matrix_, position)
                      * glm::rotate(local_matrix_, glm::radians(angle), rot_axis)
                      * glm::scale(local_matrix_, scale);
    }

    void
    Transform::update_world_matrix(const glm::mat4& parent_matrix)
    {
      world_matrix_ = parent_matrix * local_matrix_;
    }

    void
    Transform::look_at(const glm::vec3& target, const glm::vec3& up)
    {
      // FIXME: Need a position
      // Should the transform store it?
    }

    void
    Transform::look_at(const TransformPtr& transform)
    {
      // FIXME: Need a position
      // Should the transform store it?
    } */

    Transform::Transform()
              : local_pos_(0, 0, 0), world_pos_(0, 0, 0),
                local_scale_(1, 1, 1), quaternion_(1, 0, 0, 0)
    { }

    void
    Transform::rotate(float angle, glm::vec3 axis)
    {
      glm::quat rotation_quat = glm::angleAxis(glm::radians(angle), axis);
      rotate(rotation_quat);
    }

    void
    Transform::rotate(const glm::quat& quaternion)
    {
      quaternion_ = quaternion * quaternion_;
    }

    const glm::vec3
    Transform::get_direction() const
    {
      return quaternion_ * glm::vec3(0, 0, -1);
    }

    const glm::vec3
    Transform::get_up() const
    {
      return quaternion_ * glm::vec3(0, 1, 0);
    }

    const glm::vec3
    Transform::get_right() const
    {
      return quaternion_ * glm::vec3(1, 0, 0);
    }

    const glm::mat4&
    Transform::get_world_matrix() const
    {
      return world_matrix_;
    }

    const glm::mat4&
    Transform::get_local_matrix() const
    {
      return local_matrix_;
    }

  } // namespace Component
} // namespace Engine
