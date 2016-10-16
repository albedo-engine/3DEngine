#pragma once

#include <string>
#include <memory>
#include <vector>

class ShaderNode
{
  public:
    typedef std::vector<ShaderNode*> NodeList;

  public:
    virtual std::string toString() = 0;
    virtual const std::string getName() const = 0;

  public:
    ShaderNode* input(ShaderNode* n);
    ShaderNode* output(ShaderNode* n);

  public:
    const NodeList& getInputs() const;
    const NodeList& getOutputs() const;

  protected:
    NodeList inputs_;
    NodeList outputs_;
};