#pragma once

#include <utils/headers/common.hpp>

class RenderTarget
{
  public:
    RenderTarget(GLuint width, GLuint height);

  public:
    void
    init(GLenum internalFormat = GL_RGBA,
         GLenum format = GL_RGBA,
         GLenum dataType = GL_UNSIGNED_BYTE);

  public:
    GLuint
    getId();

  private:
    GLuint width_;
    GLuint height_;

    GLuint textureId_;
};
