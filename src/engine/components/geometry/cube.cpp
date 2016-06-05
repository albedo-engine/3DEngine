#include <iostream>
#include "cube.hpp"

namespace Engine
{
  namespace Components
  {
    Cube::Cube()
            : Geometry(initVertices(), initIndices())
    { }

    Cube::VertexList
    Cube::initVertices()
    {
      VertexList vertices;
      GLfloat v_positions[] =
              {
                      // Top
                      1.0f, 1.0f, -1.0f,
                      -1.0f, 1.0f, 1.0f,
                      1.0f, 1.0f, 1.0f,
                      1.0f, 1.0f, -1.0f,
                      -1.0f, 1.0f, -1.0f,
                      -1.0f, 1.0f, 1.0f,
                      // Bottom
                      -1.0f, -1.0f, 1.0f,
                      1.0f, -1.0f, -1.0f,
                      1.0f, -1.0f, 1.0f,
                      -1.0f, -1.0f, -1.0f,
                      1.0f, -1.0f, -1.0f,
                      -1.0f, -1.0f, 1.0f,
                      // Front
                      1.0f, -1.0f, -1.0f,
                      -1.0f, 1.0f, -1.0f,
                      1.0f, 1.0f, -1.0f,
                      -1.0f, 1.0f, -1.0f,
                      1.0f, -1.0f, -1.0f,
                      -1.0f, -1.0f, -1.0f,
                      // Back
                      -1.0f, 1.0f, 1.0f,
                      -1.0f, -1.0f, 1.0f,
                      1.0f, 1.0f, 1.0f,
                      -1.0f, -1.0f, 1.0f,
                      1.0f, -1.0f, 1.0f,
                      1.0f, 1.0f, 1.0f,
                      // Left
                      -1.0f, -1.0f, 1.0f,
                      -1.0f, 1.0f, -1.0f,
                      -1.0f, -1.0f, -1.0f,
                      -1.0f, 1.0f, -1.0f,
                      -1.0f, -1.0f, 1.0f,
                      -1.0f, 1.0f, 1.0f,
                      // Right
                      1.0f, -1.0f, -1.0f,
                      1.0f, 1.0f, -1.0f,
                      1.0f, 1.0f, 1.0f,
                      1.0f, 1.0f, 1.0f,
                      1.0f, -1.0f, 1.0f,
                      1.0f, -1.0f, -1.0f,
              };
      GLfloat normals[] =
              {
                      // top
                      0.f, 1.f, 0.f,
                      0.f, 1.f, 0.f,
                      0.f, 1.f, 0.f,
                      0.f, 1.f, 0.f,
                      0.f, 1.f, 0.f,
                      0.f, 1.f, 0.f,
                      // bottom
                      0.f, -1.f, 0.f,
                      0.f, -1.f, 0.f,
                      0.f, -1.f, 0.f,
                      0.f, -1.f, 0.f,
                      0.f, -1.f, 0.f,
                      0.f, -1.f, 0.f,
                      // front
                      0.f, 0.f, -1.f,
                      0.f, 0.f, -1.f,
                      0.f, 0.f, -1.f,
                      0.f, 0.f, -1.f,
                      0.f, 0.f, -1.f,
                      0.f, 0.f, -1.f,
                      // back
                      0.f, 0.f, 1.f,
                      0.f, 0.f, 1.f,
                      0.f, 0.f, 1.f,
                      0.f, 0.f, 1.f,
                      0.f, 0.f, 1.f,
                      0.f, 0.f, 1.f,
                      // left
                      -1.f, 0.f, 0.f,
                      -1.f, 0.f, 0.f,
                      -1.f, 0.f, 0.f,
                      -1.f, 0.f, 0.f,
                      -1.f, 0.f, 0.f,
                      -1.f, 0.f, 0.f,
                      // right
                      1.f, 0.f, 0.f,
                      1.f, 0.f, 0.f,
                      1.f, 0.f, 0.f,
                      1.f, 0.f, 0.f,
                      1.f, 0.f, 0.f,
                      1.f, 0.f, 0.f,
              };

      GLfloat texcoords[] =
              {
                      // top
                      1.f, 0.f,
                      0.f, 1.f,
                      1.f, 1.f,
                      1.f, 0.f,
                      0.f, 0.f,
                      0.f, 1.f,
                      // bottom
                      0.f, 0.f,
                      1., 1.,
                      1.f, 0.,
                      0.f, 1.f,
                      1.f, 1.f,
                      0.f, 0.f,
                      // front
                      0.f, 1.f,
                      1.f, 0.f,
                      0.f, 0.f,
                      1.f, 0.f,
                      0.f, 1.f,
                      1.f, 1.f,
                      // back
                      0.f, 0.f,
                      0.f, 1.f,
                      1.f, 0.f,
                      0.f, 1.f,
                      1.f, 1.f,
                      1.f, 0.f,
                      // left
                      1.f, 1.f,
                      0.f, 0.f,
                      0.f, 1.f,
                      0.f, 0.f,
                      1.f, 1.f,
                      1.f, 0.f,
                      // right
                      1.f, 1.f,
                      1.f, 0.f,
                      0.f, 0.f,
                      0.f, 0.f,
                      0.f, 1.f,
                      1.f, 1.f
              };


      for (int i = 0; i < 108; i += 3)
      {
        Vertex v;
        v.position = glm::vec3(v_positions[i], v_positions[i + 1],
                               v_positions[i + 2]);
        v.normal = glm::vec3(normals[i], normals[i + 1], normals[i + 2]);

        vertices.push_back(v);
      }

      int j = 0;
      for (int i = 0; i < 36; i += 2)
        vertices[j++].texcoords = glm::vec2(texcoords[i], texcoords[i + 1]);

      return vertices;
    }

    Cube::IndexList
    Cube::initIndices()
    {
      GLuint idx[] = {
              0,  1,  2,  3,  4,  5,
              6,  7,  8,  9,  10, 11,
              12, 13, 14, 15, 16, 17,
              18, 19, 20, 21, 22, 23,
              24, 25, 26, 27, 28, 29,
              30, 31, 32, 33, 34, 35
      };

      return IndexList(idx, idx + 36);
    }
  }
}