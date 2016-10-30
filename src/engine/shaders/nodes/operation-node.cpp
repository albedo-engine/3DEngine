#include "operation-node.hpp"

namespace Engine
{
  namespace Shader
  {
    const char* OperationNode::STRING_OPERATORS[4] =
    {
      "+",
      "-",
      "*",
      "/"
    };

    std::string
    OperationNode::toString()
    {
      if (outputs_.size() == 0)
        throw std::logic_error("ShaderNode: the OperationShaderNode"
                                 "does not have any output variable");
      if (outputs_.size() > 1)
        throw std::logic_error("ShaderNode: the OperationShaderNode"
                                 "cannot have more than one output variable");
      if (inputs_.size() < 2)
        throw std::logic_error("ShaderNode: the OperationShaderNode"
                                 "should have at least two rvalues");

      std::string str =
        outputs_[0]->toString() + " = " + inputs_[0]->toString();
      for (size_t i = 1; i < inputs_.size(); ++i)
        str += " " + std::string(STRING_OPERATORS[operation_]) +
               " " + inputs_[i]->toString();
      str += ";";

      return str;
    }

    const
    std::string OperationNode::getName() const
    {
      return STRING_OPERATORS[operation_];
    }

    OperationNode*
    OperationNode::setOperation(Operation op)
    {
      operation_ = op;
    }
  } // namespace Shader
} // namespace Engine