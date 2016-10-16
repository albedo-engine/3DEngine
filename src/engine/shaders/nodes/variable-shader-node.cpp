#include "variable-shader-node.hpp"

std::string VariableShaderNode::toString()
{
  return "";
}

void
VariableShaderNode::setName(std::string name)
{
  name_ = name;
}

void VariableShaderNode::setType(std::string type)
{
  type_ = type;
}

const std::string
VariableShaderNode::getName() const
{
  return name_;
}

const std::string
VariableShaderNode::getType() const
{
  return type_;
}