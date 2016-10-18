#pragma once

#include "shader-node.hpp"

class CallShaderNode : public ShaderNode
{
  public:
    virtual std::string toString();
    virtual const std::string getName() const;

  public:
    CallShaderNode* setName(std::string name);
    CallShaderNode* setReturnType(std::string type);
    const std::string getReturnType() const;

  private:
    std::string name_;
    std::string returnType_;
};
