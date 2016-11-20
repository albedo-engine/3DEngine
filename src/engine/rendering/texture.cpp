#include "texture.hpp"

namespace Engine
{
  namespace Rendering
  {
    Texture::Texture(GLuint width, GLuint height)
      : width_{width}
      , height_{height}
      , minFilteringMode_{GL_LINEAR}
      , maxFilteringMode_{GL_LINEAR}
      , internalFormat_{GL_RGBA}
      , format_{GL_RGBA}
      , dataType_{GL_UNSIGNED_BYTE}
    {}

    void
    Texture::setInternalFormat(GLint f)
    {
      internalFormat_ = f;
    }

    void
    Texture::setFormat(GLenum f)
    {
      format_ = f;
    }

    void
    Texture::setDataType(GLenum type)
    {
      dataType_ = type;
    }

    void
    Texture::setMinFilteringMode(GLint filteringMode)
    {
      minFilteringMode_ = filteringMode;
    }

    void
    Texture::setMaxFilteringMode(GLint filteringMode)
    {
      maxFilteringMode_ = filteringMode;
    }

    void
    Texture::setMinMaxFilteringMode(GLint minFiltering, GLint maxFiltering)
    {
      setMinFilteringMode(minFiltering);
      setMaxFilteringMode(maxFiltering);
    }

    GLuint
    Texture::getTextureId() const
    {
      return textureId_;
    }

  } // namespace Rendering
} // namespace Engine