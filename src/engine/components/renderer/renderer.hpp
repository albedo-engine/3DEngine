#pragma once

#include <utils/headers/common.hpp>
#include <components/component.hpp>
#include <components/geometry/quad.hpp>
#include <rendering/shader.hpp>
#include <components/transform/transform.hpp>
#include <components/material/material.hpp>

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
        create(int width, int height)
        {
          return std::make_shared<Renderer>(width, height);
        }

      public:
        Renderer(int width, int height);
        ~Renderer();

      public:
        bool unique() override;

      public:
        void render();
        void display();

      private:
        const GLchar* get_quad_vertex_shader();
        const GLchar* get_quad_fragment_shader();

      private:
        int renderWidth_;
        int renderHeight_;

        Rendering::Shader quadShader_;
        Components::Geometry::GeometryPtr quadGeometry_;

        GLuint frameBuffer_;
        GLuint renderBuffer_;
        GLuint renderTexture_;
    };
  } // namespace Component
} // namespace Engine
