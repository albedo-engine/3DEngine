#pragma once

#include "geometry.hpp"

namespace Engine
{
  namespace Components
  {
    class Cube : public Geometry
    {
      public:
        typedef std::shared_ptr<Cube>     CubePtr;

      public:
        CubePtr
        inline static
        create()
        {
          return std::make_shared<Cube>();
        }

      public:
        Cube();

      private:
        VertexList initVertices();
        IndexList initIndices();
    };
  } // namespace Components
} // namespace Engine
