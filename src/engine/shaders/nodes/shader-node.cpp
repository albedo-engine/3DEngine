#include "shader-node.hpp"

namespace Engine
{
  namespace Shader
  {
    ShaderNode*
    ShaderNode::input(ShaderNode* n)
    {
      inputs_.push_back(n);
      return this;
    }

    ShaderNode*
    ShaderNode::output(ShaderNode* n)
    {
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
  } // namespace Shader
} // namespace Engine