#pragma once

#include "../../../utils/headers/common.hpp"
#include "components/component.hpp"

namespace Engine
{
  namespace Components
  {
    class Transform : public Component
    {
      enum Reference {
        LOCAL,
        WORLD
      };

      public:
        typedef std::shared_ptr<Transform>  TransformPtr;

      public:
        TransformPtr
        static inline
        create()
        {
          return std::make_shared<Transform>();
        }

      public:
        /*Transform();
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
        void look_at(const TransformPtr& transform); */

        Transform();

        void rotate(float angle_degrees, glm::vec3 axis);
        void rotate(const glm::quat& quaternion);

        const glm::vec3 get_direction() const;
        const glm::vec3 get_up() const;
        const glm::vec3 get_right() const;

        const glm::mat4& get_world_matrix() const;
        const glm::mat4& get_local_matrix() const;

    private:
      glm::vec3 local_pos_;
      glm::vec3 world_pos_;
      glm::vec3 local_scale_;
      glm::quat quaternion_;
      glm::mat4 world_matrix_;
      glm::mat4 local_matrix_;

    };
  } // namespace Component
} // namespace Engine
