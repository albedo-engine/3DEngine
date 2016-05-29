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

      public:
        bool unique() override;

      public:
        // void render();

      private:
        const GLchar* get_quad_vertex_shader();
        const GLchar* get_quad_fragment_shader();

      private:
        Rendering::Shader quadShader_;

    };
  } // namespace Component
} // namespace Engine
