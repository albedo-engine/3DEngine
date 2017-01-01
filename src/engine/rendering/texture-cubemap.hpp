#pragma once

#include "texture.hpp"

namespace Engine
{
  namespace Rendering
  {
    class TextureCubemap : public Texture
    {
      public:
        typedef std::shared_ptr<TextureCubemap> TextureCubemapPtr;
        typedef std::vector<const unsigned char*> RawImageList;

      public:
        TextureCubemapPtr
        static inline
        create(uint width, uint height)
        {
          return std::make_shared<TextureCubemap>(width, height);
        }

      public:
        TextureCubemap(GLuint width, GLuint height);

      public:
        void
        load(RawImageList& imageList);
    };
  } // namespace Rendering
} // namespace Engine