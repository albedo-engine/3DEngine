#include "variable-shader-node.hpp"

std::string VariableShaderNode::toString()
{
  return name_;
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

void VariableShaderNode::setPrefix(std::string prefix)
{
  prefix_ = prefix;
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

const std::string
VariableShaderNode::getPrefix() const
{
  return prefix_;
}
