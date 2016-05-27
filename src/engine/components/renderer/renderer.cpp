#include "renderer.hpp"

namespace Engine
{
  namespace Components
  {
    Renderer::Renderer()
      : quadShader_(Rendering::Shader::createFromFiles("vertex", "fragment"))
    {
      if (!quadShader_.compile())
        throw std::runtime_error("Quad shader errors: "
                                 + std::string(quadShader_.get_compilation_info()));
    }

  } // namespace Components
} // namespace Engine
