#pragma once

#include "../../utils/headers/common.hpp"
#include "../components/component.hpp"

namespace Engine
{
  namespace Geometry
  {
    struct Vertex
    {
      glm::vec3 position;
      glm::vec3 normal;
      glm::vec2 text_coords;
    }

    class Geometry : public std::enable_shared_from_this<Geometry>
    {
      public:
        Geometry();

      private:
        std::vector<Vertex> vertices_;
    };
  } // namespace Geometry
} // namespace Geometry
