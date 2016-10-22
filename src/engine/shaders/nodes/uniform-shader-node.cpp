#include "uniform-shader-node.hpp"

std::string
UniformShaderNode::toString()
{
  return name_;
}

void
UniformShaderNode::setType(std::string type)
{
  type_ = type;
}

const
std::string UniformShaderNode::getType() const
{
  return type_;
}

void
UniformShaderNode::setDefaultValue(std::string value)
{
  defaultValue_ = value;
}

const
std::string UniformShaderNode::getDefaultValue() const
{
  return defaultValue_;
}

void
UniformShaderNode::setName(std::string name)
{
  name_ = name;
}

const
std::string UniformShaderNode::getName() const
{
  return name_;
}