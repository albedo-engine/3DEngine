#pragma once

#include "shader-node.hpp"

namespace Engine
{
  namespace Shader
  {
    class CallNode : public ShaderNode
    {
      public:
        virtual
        std::string
        toString();

        virtual
        const std::string
        getName() const;

      public:
        CallNode*
        setName(std::string name);

        CallNode*
        setReturnType(std::string type);

        const std::string
        getReturnType() const;

      private:
        std::string name_;
        std::string returnType_;
    };
  } // namespace Shader
} // namespace Engine