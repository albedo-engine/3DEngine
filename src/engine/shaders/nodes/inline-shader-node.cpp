#include "inline-shader-node.hpp"

std::string
InlineShaderNode::toString()
{
  if (text_.empty())
    throw std::logic_error("ShaderNode: the InlineShaderNode is empty");

  for (size_t i = 0; i < inputs_.size(); ++i)
  {
    std::string toReplace = "${input" + std::to_string(i) + "}";
    std::size_t pos = text_.find(toReplace);
    while (pos != std::string::npos)
    {
      text_.replace(pos, toReplace.size(), inputs_[i]->getName());
      pos = text_.find(toReplace);
    }
  }

  for (size_t i = 0; i < outputs_.size(); ++i)
  {
    std::string toReplace = "${output" + std::to_string(i) + "}";
    std::size_t pos = text_.find(toReplace);
    while (pos != std::string::npos)
    {
      text_.replace(pos, toReplace.size(), outputs_[i]->getName());
      pos = text_.find(toReplace);
    }
  }

  if (text_.find("${") != std::string::npos)
    throw std::logic_error("ShaderNode: the InlineShaderNode inputs/outputs does not match the one to replace");

  return text_;
}

const std::string
InlineShaderNode::getName() const
{
  return "InlineNode";
}

InlineShaderNode*
InlineShaderNode::text(std::string text)
{
  this->text_ = text;
  return this;
}