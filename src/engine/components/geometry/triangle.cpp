#include "triangle.hpp"

namespace Engine
{
  namespace Components
  {
    Triangle::Triangle()
            : Geometry(init())
    { }

    Triangle::VertexList
    Triangle::init()
    {
      std::vector<Vertex> vertices;
      GLfloat v_positions[] =
      {
          -0.5f, -0.5f, 0.0f,
          0.5f, -0.5f, 0.0f,
          0.0f,  0.5f, 0.0f
      };
      GLfloat normals[] =
      {
          0.0f, 0.0f, 1.0f,
          0.0f, 0.0f, 1.0f,
          0.0f, 0.0f, 1.0f
      };

      for (int i = 0; i < 9; ++i)
      {
        Vertex v;
        v.position = glm::vec3(v_positions[i], v_positions[i + 1], v_positions[i + 2]);
        v.position = glm::vec3(normals[i], normals[i + 1], normals[i + 2]);

        vertices.push_back(v);

        i += 3;
      }

      return vertices;
    }
  }
}