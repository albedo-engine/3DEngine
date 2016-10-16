#include "call-shader-node.hpp"

std::string CallShaderNode::toString()
{
  return "";
}

const std::string CallShaderNode::getName() const
{
  return name_;
}

void CallShaderNode::setName(std::string name)
{
  name_ = name;
}

void CallShaderNode::setReturnType(std::string returnType)
{
  returnType_ = returnType;
}

const std::string CallShaderNode::getReturnType() const
{
  return returnType_;
}
