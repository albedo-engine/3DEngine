#include "triangle.hpp"

namespace Engine
{
  namespace Components
  {
    Triangle::Triangle()
      : Geometry(initVertices(), initIndices())
    { }

    Triangle::VertexList
    Triangle::initVertices()
    {
      std::vector<Vertex> vertices;
      GLfloat positions[] =
        {
          -1.0f, -1.0f, 0.0f,
          1.0f, -1.0f, 0.0f,
          0.0f, 1.0f, 0.0f
        };
      GLfloat normals[] =
        {
          0.0f, 0.0f, 1.0f,
          0.0f, 0.0f, 1.0f,
          0.0f, 0.0f, 1.0f
        };

      GLfloat texcoords[] =
        {
          0.0f, 0.0f,
          1.0f, 0.0f,
          0.5f, 1.0f
        };

      for (int i = 0; i < 9; i += 3)
      {
        Vertex v;
        v.position = glm::vec3(positions[i], positions[i + 1],
                               positions[i + 2]);
        v.normal = glm::vec3(normals[i], normals[i + 1], normals[i + 2]);

        vertices.push_back(v);
      }

      int j = 0;
      for (int i = 0; i < 6; i += 2)
        vertices[j++].texcoords = glm::vec2(texcoords[i], texcoords[i + 1]);

      return vertices;
    }

    Triangle::IndexList
    Triangle::initIndices()
    {
      GLuint idx[] = {
        0, 1, 2
      };
      return IndexList(idx, idx + 3);
    }
  }
}