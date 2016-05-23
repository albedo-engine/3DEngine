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

    const std::vector<Vertex> &
    Geometry::get_vertices() const
    {
      return vertices_;
    }

    void
    Geometry::init()
    {

      glGenVertexArrays(1, &this->vao_);
      glGenBuffers(1, &this->vbo_);

      glBindVertexArray(this->vao_);
      glBindBuffer(GL_ARRAY_BUFFER, this->vbo_);

      glBufferData(GL_ARRAY_BUFFER, this->vertices_.size() * sizeof(Vertex),
                   &this->vertices_[0], GL_STATIC_DRAW);

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
