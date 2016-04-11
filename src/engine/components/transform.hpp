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
        Transform(glm::vec3 position);
        Transform(glm::vec3 scale, glm::vec3 rotation, float angle);

        void translate(glm::vec3 position);
        void translate(double x, double y, double z);

        void rotate(double angle, glm::vec3 axis);
        void rotate(double angle, double xaxis, double yaxis, double zaxis);

        void scale(glm::vec3 scale_vector);
        void scale(double scale_x, double scale_y, double scale_z);

      private:
        glm::mat4 world_matrix_;

    };
  } // namespace Component
} // namespace Engine
