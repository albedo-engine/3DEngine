#include "transform.hpp"

#include <iostream>

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
      this->translateTo(localPos_ + position);
    }

    void
    Transform::translate(float amount, Direction dir)
    {
      switch (dir)
      {
        case FORWARD:
          this->translate(getDirection() * amount);
          break;
        case BACKWARD:
          this->translate(-1.0f * getDirection() * amount);
          break;
        case EASTWARD:
          this->translate(getRight() * amount);
          break;
        case WESTWARD:
          this->translate(-1.0f * getRight() * amount);
          break;
        case UPWARD:
          this->translate(getUp() * amount);
          break;
        case DOWNWARD:
          this->translate(-1.0f * getUp() * amount);
          break;
        default:
          throw std::logic_error("Transform: Invalid direction in translate method.");
      }
    }

    void
    Transform::translateTo(const glm::vec3& position)
    {
      localPos_ = position;
      this->dirty_ = true;
    }

    void
    Transform::rotate(float angle, const glm::vec3& axis)
    {
      glm::vec3 normalized_axis = glm::normalize(axis);
      glm::quat rotation_quat = glm::angleAxis(glm::radians(angle), normalized_axis);
      this->rotate(rotation_quat);
    }

    void
    Transform::rotate(const glm::quat& quaternion)
    {
      this->rotateTo(glm::normalize(quaternion) * quaternion_);
    }

    void
    Transform::rotateTo(const glm::quat& quaternion)
    {
      quaternion_ = quaternion;
      dirty_ = true;
    }

    void
    Transform::scale(const glm::vec3& scale)
    {
      this->scaleTo(localScale_ * scale);
    }

    void
    Transform::scaleTo(const glm::vec3& scale)
    {
      localScale_ = scale;
      dirty_ = true;
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

      dirty_ = true;
    }

    void
    Transform::lookAt(const Transform::TransformPtr& transform_target)
    {
      lookAt(transform_target->getWorldPos());
    }

    void
    Transform::computeWorldMatrix(const Transform::TransformPtr& parentTransform)
    {
      bool dirty = dirty_ || (parentTransform && parentTransform->isDirty());
      if (!dirty)
        return;

      auto localMatrix = glm::translate(glm::mat4(1.0), localPos_)
                         * glm::mat4_cast(quaternion_)
                         * glm::scale(glm::mat4(1.0), localScale_);

      worldMatrix_ = (parentTransform)? parentTransform->getWorldMatrix() * localMatrix : localMatrix;
    }

    void
    Transform::setDirty(bool dirty)
    {
      dirty_ = dirty;
    }

    glm::vec3
    Transform::getLocalPos() const
    {
      return localPos_;
    }

    glm::vec3
    Transform::getWorldPos()
    {
      return glm::vec3(worldMatrix_[3]);
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
      return worldMatrix_;
    }

    bool
    Transform::isDirty() const
    {
      return dirty_;
    }

  } // namespace Component
} // namespace Engine
