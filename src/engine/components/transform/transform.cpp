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
    }

    bool
    Transform::unique()
    {
      return true;
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

      // Updates world position according to parent world position
      if (parent_ == nullptr)
      {
        world_pos_ = local_pos_;
        return;
      }

      auto parent_transform = parent_->component<Transform>();
      if (parent_transform == nullptr)
      {
        world_pos_ = local_pos_;
        return;
      }
      world_pos_ = parent_transform->get_world_position() + local_pos_;
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

    void
    Transform::look_at(const glm::vec3& source_point, const glm::vec3& dest_point)
    {
      const auto world_forward = glm::vec3(0, 0, -1);
      const auto source_target_dir = glm::normalize(dest_point - source_point);
      const auto transform_dir = get_direction();
      const auto up = get_up();
      float dot = glm::dot(world_forward, source_target_dir);

      // Check for global axis alignment
      if (glm::abs(dot + 1.0f) < 0.000001f)
      {
        quaternion_ = glm::quat(up.x, up.y, up.z, glm::pi<float>());
        return;
      }
      if (glm::abs(dot - 1.0f < 0.000001f))
      {
        quaternion_ = glm::quat(0, 0, 0, 1);
        return;
      }

      // Update the quaternion to match the new direction
      float rot_angle = glm::acos(dot);
      glm::vec3 rot_axis = glm::normalize(glm::cross(world_forward, source_target_dir));

      float half_angle = rot_angle * 0.5f;
      float s = glm::sin(half_angle);

      quaternion_.x = rot_axis.x * s;
      quaternion_.y = rot_axis.y * s;
      quaternion_.z = rot_axis.z * s;
      quaternion_.w = glm::cos(half_angle);
    }

    void
    Transform::look_at(const glm::vec3& target)
    {
      look_at(world_pos_, target);
    }

    void
    Transform::look_at(const Transform::TransformPtr& transform_target)
    {
      look_at(world_pos_, transform_target->get_world_position());
    }

    glm::vec3
    Transform::get_local_position() const
    {
      return local_pos_;
    }

    glm::vec3
    Transform::get_world_position() const
    {
      return world_pos_;
    }

    glm::vec3
    Transform::get_direction() const
    {
      return quaternion_ * glm::vec3(0, 0, -1);
    }

    glm::vec3
    Transform::get_up() const
    {
      return quaternion_ * glm::vec3(0, 1, 0);
    }

    glm::vec3
    Transform::get_right() const
    {
      return quaternion_ * glm::vec3(1, 0, 0);
    }

    const glm::mat4&
    Transform::get_world_matrix() const
    {
      // FIXME: compute the world matrix with parent
      return world_matrix_;
    }

  } // namespace Component
} // namespace Engine
