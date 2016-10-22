#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

#include "nodes/shader-node.hpp"
#include "nodes/variable-shader-node.hpp"
#include "nodes/uniform-shader-node.hpp"

class ShaderGenerator
{
  public:
    ShaderGenerator(std::string name);
    ~ShaderGenerator();

  public:
    std::vector<std::string> generateShader();

  public:
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
    void include(std::string text);
    VariableShaderNode* createVariable(std::string type,
                                       std::string name,
                                       std::string prefix = "");
    UniformShaderNode* requestUniform(std::string type,
                                      std::string name,
                                      std::string defaultValue = "");

    void traverse(ShaderNode* node);

  private:
    std::string                                           name_;
    std::vector<std::string>                              vertexStack_;
    std::vector<std::string>                              fragmentStack_;

    std::vector<std::string>                              includeStack_;

    std::unordered_map<std::string, VariableShaderNode*>  variablesMap_;
    std::unordered_map<std::string, UniformShaderNode*>   uniformMap_;

    std::unordered_map<ShaderNode*, bool>                 nodes_;
};
