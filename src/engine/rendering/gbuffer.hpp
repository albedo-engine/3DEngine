#pragma once

#include "render-target.hpp"

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

    RenderTarget& getNormalRT();
    RenderTarget& getBaseColorRT();
    RenderTarget& getDepthRT();

  private:
    GLuint framebufferId_;

    RenderTarget normalRT_; ///< normal, roumaterial ID
    RenderTarget baseColorRT_; ///< base color, material data
    RenderTarget metalRoughSpecAORT_; ///< metalness, specular, roughness and AO
    RenderTarget depthRT_; ///< depth
};
