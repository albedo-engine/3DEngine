#pragma once

#include <utils/headers/common.hpp>
#include <components/component.hpp>
#include <rendering/shader.hpp>
#include <components/transform/transform.hpp>
#include <components/material/material.hpp>
#include <components/camera/camera.hpp>

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
        create(Scene::Node::NodePtr camera, int width, int height)
        {
          return std::make_shared<Renderer>(camera, width, height);
        }

      public:
        Renderer(Scene::Node::NodePtr camera, int width, int height);
        ~Renderer();

      public:
        bool unique() override;

      public:
        void render(Scene::Node::NodePtr node);
        void display();

      private:
        const GLchar* get_gbuffer_vertex_shader();
        const GLchar* get_gbuffer_fragment_shader();

      private:
        int renderWidth_;
        int renderHeight_;

        Camera::CameraPtr camera_;

        Rendering::Shader gBufferShader_;

        GLuint gFrameBuffer_;

        // Position, Diffuse, Normal, Texcoords
        GLuint gTextures[4];
        GLuint gDepthTexture;

    };
  } // namespace Component
} // namespace Engine
