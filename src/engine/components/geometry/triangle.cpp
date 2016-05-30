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

      for (int i = 0; i < 3; i += 3)
      {
        Vertex v;
        v.position = glm::vec3(positions[i], positions[i + 1],
                               positions[i + 2]);
        v.normal = glm::vec3(normals[i], normals[i + 1], normals[i + 2]);
        v.texcoords = glm::vec3(texcoords[i], texcoords[i + 1], texcoords[i + 2]);

        vertices.push_back(v);
      }

      return vertices;
    }

    Triangle::IndexList
    Triangle::initIndices()
    {
      GLuint idx[] = {
              0, 1, 2
      };
      IndexList indices(idx, idx + 3);

      return indices;
    }
  }
}