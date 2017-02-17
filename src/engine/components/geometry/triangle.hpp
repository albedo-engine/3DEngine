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

      public:
        TrianglePtr
        inline static
        create()
        {
          return TrianglePtr(new Triangle());
        }

      private:
        Triangle();

      private:
        VertexList initVertices();
        IndexList initIndices();
    };
  } // namespace Components
} // namespace Engine
