#pragma once

#include <lib/glad/glad.hpp>
#include <lib/glm/glm/glm.hpp>
#include <component/component.hpp>

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

        ~Geometry();

      public:
        bool
        unique() override;

      public:
        const VertexList&
        getVertices() const;

        const IndexList&
        getIndices() const;

        const GLuint&
        getVao() const;

        const GLuint&
        getVbo() const;

        const GLuint&
        getEbo() const;

      private:
        void
        init();

      private:
        VertexList  vertices_;
        IndexList   indices_;

        GLuint      vao_;
        GLuint      vbo_;
        GLuint      ebo_;
    };
  }
} // namespace Engine
