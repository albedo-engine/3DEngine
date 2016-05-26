#pragma once

#include "../../../utils/headers/common.hpp"
#include "../../scene/node.hpp"
#include "components/component.hpp"

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
        typedef std::shared_ptr<Scene::Node>  NodePtr;
        typedef std::shared_ptr<Transform>    TransformPtr;

      public:
        TransformPtr
        static inline
        create(NodePtr parent_node)
        {
          return std::make_shared<Transform>(parent_node);
        }

      public:
        Transform(NodePtr parent_node);

        void translate(const glm::vec3& translation_vector);
        void translate(float amount, Direction relative_direction);

        void rotate(float angle_degrees, const glm::vec3& axis);
        void rotate(const glm::quat& quaternion);

        void scale(const glm::vec3& scale_vector);

        void look_at(const glm::vec3& target);
        void look_at(const Transform& transform_target);

        const glm::vec3& get_local_position() const;
        const glm::vec3& get_world_position() const;

        const glm::vec3& get_direction() const;
        const glm::vec3& get_up() const;
        const glm::vec3& get_right() const;

        const glm::mat4& get_world_matrix() const;

      private:
        glm::vec3 local_pos_;
        glm::vec3 local_scale_;
        glm::quat quaternion_;

        glm::vec3 world_pos_;
        glm::mat4 world_matrix_;

    };
  } // namespace Component
} // namespace Engine
