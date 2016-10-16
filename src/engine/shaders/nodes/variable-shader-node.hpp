#pragma once

#include <string>
#include <memory>

#include "shader-node.hpp"

class VariableShaderNode : public ShaderNode
{
  public:
    virtual std::string toString();
    virtual const std::string getName() const;

  public:
    void setName(std::string name);
    void setType(std::string type);
    const std::string getType() const;

  private:
    std::string name_;
    std::string type_;
};