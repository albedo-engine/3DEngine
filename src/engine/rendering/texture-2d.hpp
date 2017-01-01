#pragma once

#include <utils/headers/common.hpp>

#include "texture.hpp"

namespace Engine
{
  namespace Rendering
  {
    class Texture2D : public Texture
    {
      public:
        typedef std::shared_ptr<Texture2D> Texture2DPtr;

      public:
        Texture2DPtr
        static inline
        create(uint width, uint height)
        {
          return std::make_shared<Texture2D>(width, height);
        }

      public:
        Texture2D(GLuint width, GLuint height);

      public:
        void
        load(const unsigned char* image);

        void
        generateMipmap();

    };
  } // namespace Rendering
} // namespace Engine
