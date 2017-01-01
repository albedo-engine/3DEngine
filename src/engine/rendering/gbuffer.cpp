#include "gbuffer.hpp"

namespace Engine
{
  namespace Rendering
  {

    GBuffer::GBuffer(GLuint width, GLuint height)
      : normalRT_(width, height)
      , baseColorRT_(width, height)
      , metalRoughSpecAORT_(width, height)
      , depthRT_(width, height)
    {}

    void
    GBuffer::init()
    {
      // The following code generates each textures
      // and bind them to the framebuffer.

      glGenFramebuffers(1, &framebufferId_);
      glBindFramebuffer(GL_FRAMEBUFFER, framebufferId_);

      normalRT_.setMinMaxFilteringMode(GL_NEAREST, GL_NEAREST);
      normalRT_.load(NULL);
      glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                             GL_TEXTURE_2D, normalRT_.getTextureId(), 0);

      baseColorRT_.setMinMaxFilteringMode(GL_NEAREST, GL_NEAREST);
      baseColorRT_.load(NULL);
      glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT1,
                             GL_TEXTURE_2D, baseColorRT_.getTextureId(), 0);

      metalRoughSpecAORT_.setMinMaxFilteringMode(GL_NEAREST, GL_NEAREST);
      metalRoughSpecAORT_.load(NULL);
      glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT2,
                             GL_TEXTURE_2D, metalRoughSpecAORT_.getTextureId(), 0);

      depthRT_.setMinMaxFilteringMode(GL_NEAREST, GL_NEAREST);
      depthRT_.setInternalFormat(GL_DEPTH_COMPONENT32F);
      depthRT_.setFormat(GL_DEPTH_COMPONENT);
      depthRT_.setDataType(GL_FLOAT);
      depthRT_.load(NULL);
      glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                             GL_TEXTURE_2D, depthRT_.getTextureId(), 0);

      GLenum DrawBuffers[] = {GL_COLOR_ATTACHMENT0,
                              GL_COLOR_ATTACHMENT1,
                              GL_COLOR_ATTACHMENT2};
      glDrawBuffers(3, DrawBuffers);

      GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
      if (Status != GL_FRAMEBUFFER_COMPLETE)
      {
        throw std::runtime_error(
          "Renderer: The GBuffer could not been set up.");
      }

      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    }

    void
    GBuffer::bindRenderTargets()
    {
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, normalRT_.getTextureId());
      glActiveTexture(GL_TEXTURE1);
      glBindTexture(GL_TEXTURE_2D, baseColorRT_.getTextureId());
      glActiveTexture(GL_TEXTURE2);
      glBindTexture(GL_TEXTURE_2D, depthRT_.getTextureId());
    }

    GLuint
    GBuffer::getId()
    {
      return framebufferId_;
    }

    Texture2D& GBuffer::getNormalRT()
    {
      return normalRT_;
    }

    Texture2D& GBuffer::getBaseColorRT()
    {
      return baseColorRT_;
    }

    Texture2D& GBuffer::getDepthRT()
    {
      return depthRT_;
    }
  } // namespace Rendering
} // namespace Engine