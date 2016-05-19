#include "geometry.hpp"

namespace Engine
{
  namespace Components
  {
    namespace Geometry
    {
      Geometry::Geometry() { }

      const std::vector<Vertex> &
      Geometry::get_vertices()
      {
        return vertices_;
      }

    }
  }
}
