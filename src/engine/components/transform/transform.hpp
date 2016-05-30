#pragma once

#include "../../../utils/headers/common.hpp"
#include <scene/node.hpp>
#include <components/component.hpp>

namespace Engine
{
  namespace Components
  {
    class Transform : public Component
    {
      enum Direction {
        FORWARD,
        BACKWARD,
        WESTWARD,
        EASTWARD,
        UPWARD,
        DOWNWARD
      };

      public:
        typedef std::shared_ptr<Transform>    TransformPtr;

      public:
        TransformPtr
        static inline
        create()
        {
          return std::make_shared<Transform>();
        }

      public:
        Transform();

      public:
        bool unique() override;

      public:
        void translate(const glm::vec3& translation_vector);
        void translate(float amount, Direction relative_direction);

        void rotate(float angle_degrees, const glm::vec3& axis);
        void rotate(const glm::quat& quaternion);

        void scale(const glm::vec3& scale_vector);

        void look_at(const glm::vec3& target_point);
        void look_at(const TransformPtr& transform_target);

      public:
        glm::vec3 get_local_position() const;
        glm::vec3 get_world_position();

        glm::vec3 get_direction() const;
        glm::vec3 get_up() const;
        glm::vec3 get_right() const;

        const glm::mat4& get_world_matrix() const;

      private:
        glm::vec3 local_pos_;
        glm::vec3 local_scale_;
        glm::quat quaternion_;

        glm::mat4 world_matrix_;

    };
  } // namespace Component
} // namespace Engine
