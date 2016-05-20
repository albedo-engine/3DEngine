#include "geometry.hpp"

namespace Engine
{
  namespace Components
  {
    Geometry::Geometry(std::vector<Vertex> vertices)
              : vertices_(vertices)
    { }

    const std::vector<Vertex> &
    Geometry::get_vertices() const
    {
      return vertices_;
    }

    void
    Geometry::init()
    {
      // Generates the VAO and the VBO
      glGenVertexArrays(1, &vao_);
      glGenBuffers(1, &vbo_);

      // Binds the VBO inside the VAO binding
      glBindVertexArray(vao_);
      glBindBuffer(GL_ARRAY_BUFFER, vbo_);
      // Copies the vertices into the VBO
      glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(Vertex),
                     &vertices_[0], GL_STATIC_DRAW);
      // Sets up the different attributes at the different locations
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
      glEnableVertexAttribArray(1);

      glBindVertexArray(0);
    }
  }
}
