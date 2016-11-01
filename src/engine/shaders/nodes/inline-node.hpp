#pragma once

#include <vector>

#include "shader-node.hpp"

namespace Engine
{
  namespace Shader
  {
    class InlineNode : public ShaderNode
    {
      public:
        virtual
        const std::string
        getName() const;

      public:
        std::string
        toString() override;

        InlineNode*
        text(std::string text);

      private:
        std::string text_;
    };
  } // namespace Shader
} // namespace Engine