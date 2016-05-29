#include "geometry.hpp"

namespace Engine
{
  namespace Components
  {
    Geometry::Geometry(std::vector<Vertex> vertices)
              : vertices_(vertices)
    {
      init();
    }

    bool
    Geometry::unique()
    {
      return true;
    }

    const std::vector<Vertex> &
    Geometry::get_vertices() const
    {
      return vertices_;
    }

    const GLuint&
    Geometry::get_vao() const
    {
      return vao_;
    }

    const GLuint&
    Geometry::get_vbo() const
    {
      return vbo_;
    }

    void
    Geometry::init()
    {

      glGenVertexArrays(1, &vao_);
      glGenBuffers(1, &vbo_);

      glBindVertexArray(vao_);
      glBindBuffer(GL_ARRAY_BUFFER, vbo_);

      glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(Vertex),
                   &vertices_[0], GL_STATIC_DRAW);

      // Sends the attributes to the graphic card
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                            (GLvoid*)0);
      glEnableVertexAttribArray(1);
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                            (GLvoid*)offsetof(Vertex, normal));

      glBindVertexArray(0);
    }
  }
}
