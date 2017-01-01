#include "transform.hpp"

namespace Engine
{
  namespace Components
  {
    Transform::Transform()
              : Component()
              , localPos_(0, 0, 0)
              , localScale_(1, 1, 1)
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
      localPos_ += position;
    }

    void
    Transform::translate(float amount, Direction dir)
    {
      switch (dir)
      {
        case FORWARD:
          localPos_ += getDirection() * amount;
          break;
        case BACKWARD:
          localPos_  += (-1.0f * getDirection()) * amount;
          break;
        case EASTWARD:
          localPos_  += getRight() * amount;
          break;
        case WESTWARD:
          localPos_  += (-1.0f * getRight()) * amount;
          break;
        case UPWARD:
          localPos_  += getUp() * amount;
          break;
        case DOWNWARD:
          localPos_  += (-1.0f * getUp()) * amount;
          break;
      }
    }

    void
    Transform::translateTo(const glm::vec3& position)
    {
      localPos_ = position;
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
    Transform::rotateTo(const glm::quat& quaternion)
    {
      quaternion_ = quaternion;
    }

    void
    Transform::scale(const glm::vec3& scale)
    {
      localScale_ *= scale;
    }

    void
    Transform::scaleTo(const glm::vec3& scale)
    {
      localScale_ = scale;
    }

    void
    Transform::lookAt(const glm::vec3& target)
    {
      const auto toTarget = glm::normalize(target - getWorldPos());
      const auto direction = glm::normalize(glm::vec3(0, 0, -1));

      float cosTheta = glm::dot(direction, toTarget);
      // The direction are already aligned
      if (cosTheta >= 0.9999f)
        return;

      float half_cos = sqrt(0.5f * (1.f + cosTheta));
      glm::vec3 w = glm::cross(direction, toTarget);
      quaternion_ = glm::normalize(glm::quat(2.f * half_cos * half_cos, - w));
    }

    void
    Transform::lookAt(const Transform::TransformPtr& transform_target)
    {
      lookAt(transform_target->getWorldPos());
    }

    glm::vec3
    Transform::getLocalPos() const
    {
      return localPos_;
    }

    glm::vec3
    Transform::getWorldPos()
    {
      // Updates world position according to parent world position
      if (getTarget() == nullptr)
        return localPos_;

      auto parent_node = getTarget()->getParent();
      if (parent_node == nullptr)
        return localPos_;

      auto parent_transform = parent_node->component<Transform>();
      if (parent_transform == nullptr)
        return localPos_;

      return parent_transform->getWorldPos() + localPos_;
    }

    glm::vec3
    Transform::getDirection() const
    {
      return glm::normalize(glm::conjugate(quaternion_) * glm::vec3(0, 0, -1));
    }

    glm::vec3
    Transform::getUp() const
    {
      return glm::normalize(glm::conjugate(quaternion_) * glm::vec3(0, 1, 0));
    }

    glm::vec3
    Transform::getRight() const
    {
      return glm::normalize(glm::conjugate(quaternion_) * glm::vec3(1, 0, 0));
    }

    const glm::quat&
    Transform::getRotationQuat()
    {
      return quaternion_;
    }

    const glm::mat4&
    Transform::getWorldMatrix()
    {
      auto world_pos = getWorldPos();
      worldMatrix_ = glm::translate(glm::mat4(1.0), world_pos)
                      * glm::mat4_cast(quaternion_)
                      * glm::scale(glm::mat4(1.0), localScale_);
      return worldMatrix_;
    }

  } // namespace Component
} // namespace Engine
