#pragma once

#include <utils/headers/common.hpp>
#include <components/component.hpp>
#include <components/component-manager.hpp>

#include <rendering/shader.hpp>
#include <components/transform/transform.hpp>
#include <components/material/material.hpp>
#include <components/geometry/quad.hpp>
#include <components/camera/camera.hpp>
#include <components/light/light.hpp>

#include <rendering/gbuffer.hpp>

#include <deferred_fs.h>
#include <deferred_vs.h>
#include <gbuffer_fs.h>
#include <gbuffer_vs.h>

namespace Engine
{
  namespace Components
  {
    class Renderer : public Component
    {
      public:
        typedef std::shared_ptr<Renderer> RendererPtr;

      public:
        RendererPtr
        static inline
        create(const Scene::Node::NodePtr& camera, int width, int height)
        {
          return RendererPtr(new Renderer(camera, width, height));
        }

      public:
        ~Renderer();

      public:
        bool
        unique() override;

      public:
        void
        display();

        enum DebugOptions
        {
          SHOW_POSITION_BUFFER = 1,
          SHOW_DIFFUSE_BUFFER  = 2,
          SHOW_NORMAL_BUFFER   = 4,
          WIREFRAME_MODE       = 8,
        };

        void
        toggleDebug(unsigned int options);

      private:
        Renderer(const Scene::Node::NodePtr& camera, int width, int height);

      private:
        void
        render();

        void
        renderGeometry(const Scene::Node::NodePtr& node);

        void
        renderLights();

        void
        debugDisplay();

        void
        debugDisplayFramebuffer(GLint width, GLint height,
                                unsigned int position);

      private:
        int renderWidth_;
        int renderHeight_;

        Rendering::GBuffer        gbuffer_;
        Rendering::Shader         deferredShader_;
        Components::Quad::QuadPtr renderQuad_;

        Camera::CameraPtr camera_;

        unsigned int debugOptions_ = 0;
    };
  } // namespace Component
} // namespace Engine
