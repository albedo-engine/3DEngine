#pragma once

#include "../../utils/headers/common.hpp"

namespace Engine
{
  namespace Components
  {
    class Component
    {
      public:
        typedef std::shared_ptr<Component>    ComponentPtr;

      public:
        virtual ~Component();

    private:

    };
  } // namespace Component
} // namespace Engine
