#include "call-shader-node.hpp"

std::string CallShaderNode::toString()
{
  if (outputs_.size() > 1)
    throw std::logic_error("ShaderNode: CallShaderNode canno't have more than one output");

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

const std::string CallShaderNode::getName() const
{
  return name_;
}

CallShaderNode*
CallShaderNode::setName(std::string name)
{
  name_ = name;
  return this;
}

CallShaderNode*
CallShaderNode::setReturnType(std::string returnType)
{
  returnType_ = returnType;
  return this;
}

const std::string CallShaderNode::getReturnType() const
{
  return returnType_;
}
