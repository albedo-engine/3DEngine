#include "texture-2d.hpp"

namespace Engine
{
  namespace Rendering
  {
    Texture2D::Texture2D(GLuint width, GLuint height)
      : Texture(width, height)
    {}

    void
    Texture2D::load(const unsigned char* image)
    {
      glGenTextures(1, &textureId_);
      glBindTexture(GL_TEXTURE_2D, textureId_);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilteringMode_);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, maxFilteringMode_);

      if (internalFormat_ == GL_DEPTH_COMPONENT32F)
        glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);

      glTexImage2D(GL_TEXTURE_2D, 0, internalFormat_,
                   width_, height_, 0, format_, dataType_, image);

      glBindTexture(GL_TEXTURE_2D, 0);
    }

    void
    Texture2D::generateMipmap()
    {
      glBindTexture(GL_TEXTURE_2D, textureId_);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilteringMode_);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, maxFilteringMode_);
      glGenerateMipmap(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, 0);
    }

  } // namespace Rendering
} // namespace Engine
