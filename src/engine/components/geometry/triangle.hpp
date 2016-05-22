#pragma once

#include "geometry.hpp"

namespace Engine
{
  namespace Components
  {
    class Triangle : public Geometry
    {
      public:
        typedef std::shared_ptr<Triangle> TrianglePtr;
        typedef std::vector<Vertex>       VertexList;

      public:
        TrianglePtr
        inline static
        create()
        {
          return std::make_shared<Triangle>();
        }

      public:
        Triangle();

      private:
        VertexList init();
    };
  } // namespace Components
} // namespace Engine
