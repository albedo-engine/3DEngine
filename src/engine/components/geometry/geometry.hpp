#pragma once

#include <utils/headers/common.hpp>
#include <components/component.hpp>

namespace Engine
{
  namespace Components
  {
    struct Vertex
    {
      glm::vec3 position;
      glm::vec3 normal;
    };

    class Geometry : public Component
    {
      public:
        typedef std::shared_ptr<Geometry> GeometryPtr;

      public:
        Geometry() = delete;
        Geometry(std::vector<Vertex> vertices);

        const std::vector<Vertex>& get_vertices() const;
        const GLuint& get_vao() const;
        const GLuint& get_vbo() const;

      private:
        void init();

      private:
        std::vector<Vertex> vertices_;
        std::vector<GLuint> indices_;

        GLuint              vao_;
        GLuint              vbo_;
    };
  }
} // namespace Engine
