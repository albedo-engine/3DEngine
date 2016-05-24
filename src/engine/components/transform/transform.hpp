#pragma once

#include "../../../utils/headers/common.hpp"
#include "components/component.hpp"

namespace Engine
{
  namespace Components
  {
    class Transform : public Component
    {
      public:
        typedef std::shared_ptr<Transform>  TransformPtr;

      public:
        TransformPtr
        static inline
        create()
        {
          return std::make_shared<Transform>();
        }

        TransformPtr
        static inline
        create(glm::vec3 position)
        {
          return std::make_shared<Transform>(position);
        }

        TransformPtr
        static inline
        create(glm::vec3 scale, glm::vec3 rotation, float angle)
        {
          return std::make_shared<Transform>(scale, rotation, angle);
        }

        TransformPtr
        static inline
        create(glm::vec3 scale, glm::vec3 position, glm::vec3 rotation, float angle)
        {
          return std::make_shared<Transform>(scale, position, rotation, angle);
        }

      public:
        Transform();
        Transform(glm::vec3 position);
        Transform(glm::vec3 scale, glm::vec3 rotation, float angle);
        Transform(glm::vec3 scale, glm::vec3 position, glm::vec3 rotation, float angle);

        void translate(glm::vec3 position);
        void translate(double x, double y, double z);

        void rotate(float angle, glm::vec3 axis);
        void rotate(float angle, double xaxis, double yaxis, double zaxis);

        void scale(glm::vec3 scale_vector);
        void scale(double scale_x, double scale_y, double scale_z);

        void scale_rot_translate(glm::vec3 scale, glm::vec3 position,
                                 glm::vec3 rotation, float angle);

        void update_world_matrix(const glm::mat4& parent_matrix);
        void look_at(const glm::vec3& target, const glm::vec3& up);
        void look_at(const TransformPtr& transform);

        const glm::mat4& get_world_matrix();
        const glm::mat4& get_local_matrix();
      private:
        glm::mat4 world_matrix_;
        glm::mat4 local_matrix_;

    };
  } // namespace Component
} // namespace Engine
