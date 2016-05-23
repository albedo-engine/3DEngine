#include "engine.hpp"

namespace Engine
{
  void
  Engine::initialize()
  {
    glewExperimental = GL_TRUE;
    // Initializes GLEW
    if (glewInit() != GLEW_OK)
    {
      std::cout << "Failed to initialize GLEW" << std::endl;
      throw 1;
    }
  }
}
