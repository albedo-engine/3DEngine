#pragma once

#include "../../../utils/headers/common.hpp"

#include "../component.hpp"

namespace Engine
{
  namespace Components
  {
    namespace Geometry
    {
      struct Vertex
      {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 text_coords;
      };

      class Geometry : public Component
      {
        public:
          typedef std::shared_ptr<Geometry> GeometryPtr;

        public:
          Geometry();

          const std::vector<Vertex>& get_vertices();

        private:
          std::vector<Vertex> vertices_;
          std::vector<GLuint> indices_;

          GLuint vao_;
          GLuint vbo_;
      };

    } // namespace Geometry

  }
} // namespace Engine
