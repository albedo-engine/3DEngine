#include "variable-shader-node.hpp"

std::string VariableNode::toString()
{
  return name_;
}

void
VariableNode::setName(std::string name)
{
  name_ = name;
}

void VariableNode::setType(std::string type)
{
  type_ = type;
}

void VariableNode::setPrefix(std::string prefix)
{
  prefix_ = prefix;
}

const std::string
VariableNode::getName() const
{
  return name_;
}

const std::string
VariableNode::getType() const
{
  return type_;
}

const std::string
VariableNode::getPrefix() const
{
  return prefix_;
}
