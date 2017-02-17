#pragma once

#include "texture-2d.hpp"

namespace Engine
{
  namespace Rendering
  {
    class GBuffer
    {
      public:
        GBuffer(GLuint width, GLuint height);

      public:
        void
        init();

        void
        bindRenderTargets();

      public:
        GLuint
        getId();

        Texture2D::Texture2DPtr&
        getNormalRT();

        Texture2D::Texture2DPtr&
        getBaseColorRT();

        Texture2D::Texture2DPtr&
        getDepthRT();

      private:
        GLuint framebufferId_;

        Texture2D::Texture2DPtr normalRT_; ///< normal, material ID
        Texture2D::Texture2DPtr baseColorRT_; ///< base color, material data
        Texture2D::Texture2DPtr metalRoughSpecAORT_; ///< metalness, specular, roughness and AO
        Texture2D::Texture2DPtr depthRT_; ///< depth
    };
  } // namespace Rendering
} // namespace Engine
