#pragma once

#include "geometry.hpp"

namespace Engine
{
  namespace Components
  {
    class Quad : public Geometry
    {
      public:
        typedef std::shared_ptr<Quad> QuadPtr;

      public:
        QuadPtr
        inline static
        create()
        {
          return QuadPtr(new Quad());
        }

      private:
        Quad();

      private:
        VertexList initVertices();
        IndexList initIndices();
    };
  } // namespace Components
} // namespace Engine
