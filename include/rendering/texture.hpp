#pragma once

#include <utils/headers/common.hpp>

namespace Engine
{
  namespace Rendering
  {
    class Texture
    {
      public:
        void
        setInternalFormat(GLint format);

        void
        setFormat(GLenum format);

        void
        setDataType(GLenum type);

        void
        setMinFilteringMode(GLint filteringMode);

        void
        setMaxFilteringMode(GLint filteringMode);

        void
        setMinMaxFilteringMode(GLint minFiltering, GLint maxFiltering);

        GLuint
        getTextureId() const;

      protected:
        Texture(GLuint width, GLuint height);

      protected:
        GLuint  textureId_;

        GLuint  width_;
        GLuint  height_;

        GLint   internalFormat_;
        GLenum  format_;
        GLenum  dataType_;

        GLint   minFilteringMode_;
        GLint   maxFilteringMode_;
    };
  } // namespace Rendering
} // namespace Engine
