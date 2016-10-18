#pragma once

class UniformShaderNode : public ShaderNode
{
  public:
    virtual std::string toString();
    virtual const std::string getName() const;
};
