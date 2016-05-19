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
    };

    class Geometry : public std::enable_shared_from_this<Geometry>
    {
      public:
        typedef std::shared_ptr<Geometry>  GeometryPtr;

      public:
        Geometry();

      private:
        std::vector<Vertex> vertices_;
        std::vector<GLuint> indices_;

        GLuint vao_;
        GLuint vbo_;
    };
  } // namespace Geometry
} // namespace Geometry
