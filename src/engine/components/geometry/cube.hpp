#pragma once

#include <components/geometry/geometry.hpp>

namespace Engine
{
  namespace Components
  {
    class Cube : public Geometry
    {
      public:
        typedef std::shared_ptr<Cube> CubePtr;

      public:
        CubePtr
        inline static
        create()
        {
          return CubePtr(new Cube());
        }

      private:
        Cube();

      private:
        VertexList
        initVertices();

        IndexList
        initIndices();
    };
  } // namespace Components
} // namespace Engine
