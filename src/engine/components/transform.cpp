#include "transform.hpp"

namespace Engine
{
  namespace Components
  {
    Transform::Transform()
      : position_(glm::vec3(0.0f))
      , rotation_(glm::vec3(0.0f))
      , scale_(glm::vec3(0.0f))
    { }

    Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
      : position_(position)
      , rotation_(rotation)
      , scale_(scale)
    { }

  } // namespace Component
} // namespace Engine
