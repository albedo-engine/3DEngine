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

    bool
    Transform::unique()
    {
      return true;
    }

    void
    Transform::translate(const glm::vec3& position)
    {
      local_pos_ += position;
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
    }

    void
    Transform::translate_to(const glm::vec3& position)
    {
      local_pos_ = position;
    }

    void
    Transform::rotate(float angle, const glm::vec3& axis)
    {
      glm::vec3 normalized_axis = glm::normalize(axis);
      glm::quat rotation_quat = glm::angleAxis(glm::radians(angle), normalized_axis);
      rotate(rotation_quat);
    }

    void
    Transform::rotate(const glm::quat& quaternion)
    {
      quaternion_ = glm::normalize(quaternion) * quaternion_;
    }

    void
    Transform::rotate_to(const glm::quat& quaternion)
    {
      quaternion_ = quaternion;
    }

    void
    Transform::scale(const glm::vec3& scale)
    {
      local_scale_ += scale;
    }

    void
    Transform::scale_to(const glm::vec3& scale)
    {
      local_scale_ = scale;
    }

    void
    Transform::look_at(const glm::vec3& target)
    {
      const auto to_target = glm::normalize(target - get_world_position());
      const auto direction = glm::normalize(glm::vec3(0, 0, -1));

      float cos_theta = glm::dot(direction, to_target);
      // The direction are already aligned
      if (cos_theta >= 0.9999f)
        return;

      float half_cos = sqrt(0.5f * (1.f + cos_theta));
      glm::vec3 w = glm::cross(direction, to_target);
      quaternion_ = glm::normalize(glm::quat(2.f * half_cos * half_cos, - w));
    }

    void
    Transform::look_at(const Transform::TransformPtr& transform_target)
    {
      look_at(transform_target->get_world_position());
    }

    glm::vec3
    Transform::get_local_position() const
    {
      return local_pos_;
    }

    glm::vec3
    Transform::get_world_position()
    {
      // Updates world position according to parent world position
      if (get_target() == nullptr)
        return local_pos_;

      auto parent_node = get_target()->get_parent();
      if (parent_node == nullptr)
        return local_pos_;

      auto parent_transform = parent_node->component<Transform>();
      if (parent_transform == nullptr)
        return local_pos_;

      return parent_transform->get_world_position() + local_pos_;
    }

    glm::vec3
    Transform::get_direction() const
    {
      return glm::normalize(glm::conjugate(quaternion_) * glm::vec3(0, 0, -1));
    }

    glm::vec3
    Transform::get_up() const
    {
      return glm::normalize(glm::conjugate(quaternion_) * glm::vec3(0, 1, 0));
    }

    glm::vec3
    Transform::get_right() const
    {
      return glm::normalize(glm::conjugate(quaternion_) * glm::vec3(1, 0, 0));
    }

    const glm::quat&
    Transform::get_rotation_quat()
    {
      return quaternion_;
    }

    const glm::mat4&
    Transform::get_world_matrix()
    {
      auto world_pos = get_world_position();
      world_matrix_ = glm::translate(glm::mat4(1.0), world_pos)
                      * glm::mat4_cast(quaternion_)
                      * glm::scale(glm::mat4(1.0), local_scale_);
      return world_matrix_;
    }

  } // namespace Component
} // namespace Engine
