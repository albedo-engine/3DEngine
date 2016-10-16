#include "inline-shader-node.hpp"

std::string
InlineShaderNode::toString()
{
  if (text_.empty())
    throw std::logic_error("ShaderNode: The InlineShaderNode is empty");

  for (auto& input : inputs_)
  {
    std::size_t pos = text_.find("${" + input->getName() + "}");
    // The value to replace is found in the text
    if (pos != std::string::npos)
      text_.replace(pos, input->getName().size() + 3, input->getName());
  }

  for (auto& output : outputs_)
  {
    std::size_t pos = text_.find("${" + output->getName() + "}");
    // The value to replace is found in the text
    if (pos != std::string::npos)
      text_.replace(pos, output->getName().size() + 3, output->getName());
  }

  return text_;
}

const std::string
InlineShaderNode::getName() const
{
  return "InlineNode";
}

void
InlineShaderNode::text(std::string text)
{
  this->text_ = text;
}