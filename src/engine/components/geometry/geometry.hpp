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
      glm::vec2 texcoords;
    };

    class Geometry : public Component
    {
      public:
        typedef std::shared_ptr<Geometry> GeometryPtr;
        typedef std::vector<Vertex> VertexList;
        typedef std::vector<GLuint> IndexList;

      public:
        Geometry() = delete;

        Geometry(VertexList vertices, IndexList indices);

      public:
        bool unique() override;

      public:
        const VertexList &get_vertices() const;
        const IndexList &get_indices() const;

        const GLuint &get_vao() const;

        const GLuint &get_vbo() const;

      private:
        void init();

      private:
        VertexList vertices_;
        IndexList  indices_;

        GLuint vao_;
        GLuint vbo_;
    };
  }
} // namespace Engine
