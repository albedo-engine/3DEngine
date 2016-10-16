#include "shader-node.hpp"

ShaderNode*
ShaderNode::input(ShaderNode* n)
{
  // Adds given input
  inputs_.push_back(n);
  return this;
}

ShaderNode*
ShaderNode::output(ShaderNode* n)
{
  // Adds given outputs
  outputs_.push_back(n);
  n->input(this);

  return this;
}

const ShaderNode::NodeList&
ShaderNode::getInputs() const
{
  return inputs_;
}

const ShaderNode::NodeList&
ShaderNode::getOutputs() const
{
  return outputs_;
}