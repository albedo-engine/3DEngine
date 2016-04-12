#pragma once

#include "../../utils/headers/common.hpp"
#include "component.hpp"

namespace Engine
{
  namespace Components
  {
    class Transform : public Component
    {
      public:
        typedef std::shared_ptr<Transform>  TransformPtr;

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

      private:
        glm::mat4 world_matrix_;

    };
  } // namespace Component
} // namespace Engine
