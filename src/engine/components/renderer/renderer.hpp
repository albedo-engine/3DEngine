#pragma once

#include <utils/headers/common.hpp>
#include <components/component.hpp>
#include <rendering/shader.hpp>

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

        // void render();

      private:
        Rendering::Shader quadShader_;

    };
  } // namespace Component
} // namespace Engine
