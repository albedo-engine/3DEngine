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

        Texture2D& getNormalRT();
        Texture2D& getBaseColorRT();
        Texture2D& getDepthRT();

      private:
        GLuint framebufferId_;

        Texture2D normalRT_; ///< normal, roumaterial ID
        Texture2D baseColorRT_; ///< base color, material data
        Texture2D metalRoughSpecAORT_; ///< metalness, specular, roughness and AO
        Texture2D depthRT_; ///< depth
    };
  } // namespace Rendering
} // namespace Engine