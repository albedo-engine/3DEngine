#pragma once

#include <vector>
#include "shader-node.hpp"

class InlineShaderNode : public ShaderNode
{
  public:
    virtual const std::string getName() const;

  public:
    std::string toString() override;
    void text(std::string text);

  private:
    std::string text_;
};