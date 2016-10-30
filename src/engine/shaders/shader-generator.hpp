#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

#include "nodes/shader-node.hpp"
#include "nodes/variable-node.hpp"
#include "nodes/uniform-node.hpp"
#include "nodes/operation-node.hpp"
#include "nodes/inline-node.hpp"
#include "nodes/call-node.hpp"

#include "type-dec.hpp"

namespace Engine
{
  namespace Shader
  {
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

        TypeDec* declareStruct(std::string name);

        UniformNode* requestUniform(std::string type,
                                    std::string name,
                                    std::string defaultValue = "");

        VariableNode* createVariable(std::string type,
                                     std::string name,
                                     std::string prefix = "");

        void traverse(ShaderNode* node);

        void clean();

      private:
        std::string                                           name_;
        std::vector<std::string>                              vertexStack_;
        std::vector<std::string>                              fragmentStack_;

        std::vector<std::string>                              includeStack_;

        std::unordered_map<std::string, VariableNode*>        variablesMap_;
        std::unordered_map<std::string, TypeDec*>             typeDecMap_;
        std::unordered_map<std::string, UniformNode*>         uniformMap_;

        std::unordered_map<ShaderNode*, bool>                 nodes_;
    };

    class StructDec
    {

    };

  } // namespace Shader
} // namespace Engine