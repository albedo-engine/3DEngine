#include "geometry.hpp"

namespace Engine
{
  namespace Components
  {
    Geometry::Geometry(VertexList vertices, IndexList indices)
            : vertices_(vertices)
            , indices_(indices)
    {
      init();
    }

    Geometry::~Geometry()
    {
      glDeleteVertexArrays(1, &vao_);
      glDeleteBuffers(1, &vbo_);
      glDeleteBuffers(1, &ebo_);
    }

    bool
    Geometry::unique()
    {
      return true;
    }

    const Geometry::VertexList&
    Geometry::getVertices() const
    {
      return vertices_;
    }

    const Geometry::IndexList&
    Geometry::getIndices() const
    {
      return indices_;
    }

    const GLuint&
    Geometry::getVao() const
    {
      return vao_;
    }

    const GLuint&
    Geometry::getVbo() const
    {
      return vbo_;
    }

    const GLuint&
    Geometry::getEbo() const
    {
      return ebo_;
    }

    void
    Geometry::init()
    {
      glGenVertexArrays(1, &vao_);
      glGenBuffers(1, &vbo_);
      glGenBuffers(1, &ebo_);

      glBindVertexArray(vao_);

      // VBO
      glBindBuffer(GL_ARRAY_BUFFER, vbo_);
      glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(Vertex),
                   &vertices_[0], GL_STATIC_DRAW);

      // EBO
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(GLuint),
                   &indices_[0], GL_STATIC_DRAW);

      // Sends the attributes to the graphic card
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                            (GLvoid*)0);

      glEnableVertexAttribArray(1);
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                            (GLvoid*)offsetof(Vertex, normal));

      glEnableVertexAttribArray(2);
      glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                            (GLvoid*)offsetof(Vertex, texcoords));

      glBindVertexArray(0);
    }
  }
}
