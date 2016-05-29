#include "transform.hpp"

namespace Engine
{
  namespace Components
  {
    Transform::Transform()
              : Component()
              , local_pos_(0, 0, 0)
              , local_scale_(1, 1, 1)
              , quaternion_(1, 0, 0, 0)
    { }

    void
    Transform::translate(const glm::vec3& position)
    {
      local_pos_ += position;
      // FIXME: Compute world position
    }

    void
    Transform::translate(float amount, Direction dir)
    {
      switch (dir)
      {
        case FORWARD:
          local_pos_ += get_direction() * amount;
          break;
        case BACKWARD:
          local_pos_ += (-1.0f * get_direction()) * amount;
          break;
        case EASTWARD:
          local_pos_ += get_right() * amount;
          break;
        case WESTWARD:
          local_pos_ += (-1.0f * get_right()) * amount;
          break;
        case UPWARD:
          local_pos_ += get_up() * amount;
          break;
        case DOWNWARD:
          local_pos_ += (-1.0f * get_up()) * amount;
          break;
      }

      // FIXME: Compute world position
    }

    void
    Transform::rotate(float angle, const glm::vec3& axis)
    {
      glm::quat rotation_quat = glm::angleAxis(glm::radians(angle), axis);
      rotate(rotation_quat);
    }

    void
    Transform::rotate(const glm::quat& quaternion)
    {
      quaternion_ = quaternion * quaternion_;
    }

    void
    Transform::scale(const glm::vec3& scale)
    {
      local_scale_ = scale;
    }

    const glm::vec3&
    Transform::get_direction() const
    {
      return quaternion_ * glm::vec3(0, 0, -1);
    }

    const glm::vec3&
    Transform::get_up() const
    {
      return quaternion_ * glm::vec3(0, 1, 0);
    }

    const glm::vec3&
    Transform::get_right() const
    {
      return quaternion_ * glm::vec3(1, 0, 0);
    }

    const glm::vec3&
    Transform::get_local_position() const
    {
      return local_pos_;
    }

    const glm::vec3&
    Transform::get_world_position() const
    {
      // return nullptr;
      return glm::vec3(0.0f);
    }

    const glm::mat4&
    Transform::get_world_matrix() const
    {
      return world_matrix_;
    }

  } // namespace Component
} // namespace Engine
