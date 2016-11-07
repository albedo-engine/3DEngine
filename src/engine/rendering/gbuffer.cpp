#include "gbuffer.hpp"

GBuffer::GBuffer(GLuint width, GLuint height)
  : normalRT_(width, height)
  , baseColorRT_(width, height)
  , metalRoughSpecAORT_(width, height)
  , depthRT_(width, height)
{ }

void
GBuffer::init()
{
  // The following code generates each textures
  // and bind them to the framebuffer.

  glGenFramebuffers(1, &framebufferId_);
  glBindFramebuffer(GL_FRAMEBUFFER, framebufferId_);

  normalRT_.init();
  glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                         GL_TEXTURE_2D, normalRT_.getId(), 0);

  baseColorRT_.init();
  glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT1,
                         GL_TEXTURE_2D, baseColorRT_.getId(), 0);

  metalRoughSpecAORT_.init();
  glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT2,
                         GL_TEXTURE_2D, metalRoughSpecAORT_.getId(), 0);

  depthRT_.init(GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT, GL_FLOAT);
  glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                         GL_TEXTURE_2D, depthRT_.getId(), 0);

  GLenum DrawBuffers[] = {GL_COLOR_ATTACHMENT0,
                          GL_COLOR_ATTACHMENT1,
                          GL_COLOR_ATTACHMENT2};
  glDrawBuffers(3, DrawBuffers);

  GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if (Status != GL_FRAMEBUFFER_COMPLETE)
    throw std::runtime_error("Renderer: The GBuffer could not been set up.");

  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void
GBuffer::bindRenderTargets()
{
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, normalRT_.getId());
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, baseColorRT_.getId());
  glActiveTexture(GL_TEXTURE2);
  glBindTexture(GL_TEXTURE_2D, depthRT_.getId());
}

GLuint
GBuffer::getId()
{
  return framebufferId_;
}

RenderTarget& GBuffer::getNormalRT()
{
  return normalRT_;
}

RenderTarget& GBuffer::getBaseColorRT()
{
  return baseColorRT_;
}

RenderTarget& GBuffer::getDepthRT()
{
  return depthRT_;
}
