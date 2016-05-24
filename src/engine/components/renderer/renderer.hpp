#pragma once

#include "../../../utils/headers/common.hpp"
#include "components/component.hpp"

namespace Engine
{
  namespace Components
  {
    class Renderer : public Component
    {
      public:
        typedef std::shared_ptr<Renderer>  RendererPtr;

      public:
        RendererPtr
        static inline
        create()
        {
          return std::make_shared<Renderer>();
        }

      public:
        Renderer();

    };
  } // namespace Component
} // namespace Engine
