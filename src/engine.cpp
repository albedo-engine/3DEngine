#include <stdexcept>

#include <lib/glad/glad.hpp>
#include <engine.hpp>

namespace Engine
{
  void
  Engine::initialize(void* (*getProcAdress)(const char *name))
  {
      if (!gladLoadGLLoader((GLADloadproc)getProcAdress))
          throw new std::runtime_error("Failed to initialize GLAD");
    glEnable(GL_DEPTH_TEST);
  }
}
