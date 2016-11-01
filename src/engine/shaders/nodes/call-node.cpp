#include "call-node.hpp"

namespace Engine
{
  namespace Shader
  {
    std::string
    CallNode::toString()
    {
      if (outputs_.size() > 1)
      {
        throw std::logic_error("ShaderNode: CallShaderNode cannot have "
                               "more than one output");
      }

      std::string format = "";
      if (outputs_.size() == 1)
        format = outputs_[0]->toString() + " = ";

      format += name_ + "(";
      format += (inputs_.size()) ? inputs_[0]->toString() : "";
      for (size_t i = 1; i < inputs_.size(); ++i)
        format += ", " + inputs_[i]->toString();
      format += ");";

      return format;
    }

    const std::string
    CallNode::getName() const
    {
      return name_;
    }

    CallNode*
    CallNode::setName(std::string name)
    {
      name_ = name;
      return this;
    }

    CallNode*
    CallNode::setReturnType(std::string returnType)
    {
      returnType_ = returnType;
      return this;
    }

    const std::string
    CallNode::getReturnType() const
    {
      return returnType_;
    }
  } // namespace Shader
} // namespace Engine
