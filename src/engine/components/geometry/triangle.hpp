#pragma once

namespace Engine
{
  namespace Components
  {
    class Triangle : public Geometry
    {
      public:
        typedef std::shared_ptr<Triangle> TrianglePtr;

      public:
        Triangle();
    };
  }
}
