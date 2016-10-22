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
    void setPrefix(std::string prefix);

    const std::string getType() const;
    const std::string getPrefix() const;

  private:
    std::string name_;
    std::string type_;
    std::string prefix_;
};