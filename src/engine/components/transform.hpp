#pragma once

#include "../../utils/headers/common.hpp"
#include "component.hpp"

namespace Engine
{
  namespace Component
  {
    class Transform : public Component
    {
      public:
        typedef std::shared_ptr<Transform>  TransformPtr;

      public:
        Transform();
    };
  } // namespace Component
} // namespace Engine
