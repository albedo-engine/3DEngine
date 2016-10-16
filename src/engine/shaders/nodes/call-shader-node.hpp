#pragma once

#include "shader-node.hpp"

class CallShaderNode : ShaderNode
{
  public:
    virtual std::string toString() = 0;
    virtual const std::string getName() const = 0;

  public:
    void setName(std::string name);
    void setReturnType(std::string type);
    const std::string getReturnType() const;

  private:
    std::string name_;
    std::string returnType_;
};
