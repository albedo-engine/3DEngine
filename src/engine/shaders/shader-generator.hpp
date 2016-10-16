#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

#include "nodes/shader-node.hpp"
#include "nodes/variable-shader-node.hpp"

class ShaderGenerator
{
  public:
    ShaderGenerator(std::string name);
    ~ShaderGenerator();

  public:
    std::vector<std::string> generateShader();
    VariableShaderNode* createVariable(std::string type, std::string name);

    template <typename NodeType>
    NodeType*
    createNode()
    {
      NodeType* n = new NodeType();
      nodes_[n] = false;
      return n;
    }

  private:
    virtual ShaderNode* generateFragmentShaderGraph();

  private:
    void traverse(ShaderNode* node);

  private:
    std::string                                           name_;

    std::vector<std::string>                              vertexStack_;
    std::vector<std::string>                              fragmentStack_;

    std::unordered_map<std::string, VariableShaderNode*>  variablesMap_;
    std::unordered_map<ShaderNode*, bool>                 nodes_;
};
