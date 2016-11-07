#include "render-target.hpp"

RenderTarget::RenderTarget(GLuint width, GLuint height)
             : width_(width)
             , height_(height)
{ }

void
RenderTarget::init(GLenum internalFormat, GLenum format, GLenum dataType)
{
  glGenTextures(1, &textureId_);
  glBindTexture(GL_TEXTURE_2D, textureId_);

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  if (internalFormat == GL_DEPTH_COMPONENT32F)
    glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);

  glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width_, height_,
               0, format, dataType, NULL);
}

GLuint
RenderTarget::getId()
{
  return textureId_;
}