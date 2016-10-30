#pragma once

#include "shader-node.hpp"

namespace Engine
{
  namespace Shader
  {
    class OperationNode : public ShaderNode
    {
      private:
        static const char* STRING_OPERATORS[4];

      public:
        enum Operation
        {
          ADD,
          SUB,
          MUL,
          DIV
        };

      public:
        virtual std::string toString();
        virtual const std::string getName() const;

      public:
        OperationNode* setOperation(Operation op);

      private:
        Operation operation_;
    };
  } // namespace Shader
} // namespace Engine
