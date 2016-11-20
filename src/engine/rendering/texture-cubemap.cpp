#include "texture-cubemap.hpp"

namespace Engine
{
  namespace Rendering
  {

    TextureCubemap::TextureCubemap(GLuint width, GLuint height)
      : Texture(width, height)
    {}

    void
    TextureCubemap::load(RawImageList& imageList)
    {
      size_t size = imageList.size();
      if (imageList.size() != 6)
      {
        throw std::logic_error("Cubemap: could not load the cubemap."
                               + std::to_string(size) +
                               " images provided instead of 6.");
      }

      glGenTextures(1, &textureId_);
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_CUBE_MAP, textureId_);
      //glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
      for (size_t i = 0; i < imageList.size(); ++i)
      {
        auto rawData = imageList[i];
        /*glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
                     internalFormat_, width_, height_, 0,
                     format_, dataType_, rawData);*/
        glTexImage2D(
          GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
          GL_RGB, width_, height_, 0, GL_RGB, GL_UNSIGNED_BYTE, rawData
        );
      }

      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, minFilteringMode_);
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, maxFilteringMode_);
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
      glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }
  } // namespace Rendering
} // namespace Engine
