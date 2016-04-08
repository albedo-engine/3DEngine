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
        Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

      private:
        glm::vec3 position_;
        glm::vec3 rotation_;
        glm::vec3 scale_;
    };
  } // namespace Component
} // namespace Engine
