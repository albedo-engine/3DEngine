#pragma once

#include <string>
#include <memory>
#include <unordered_map>

#include "shader-node.hpp"

namespace Engine
{
  namespace Shader
  {
    class VariableNode : public ShaderNode
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

    class StructVariableNode : public VariableNode
    {
      public:
        typedef std::unordered_map<std::string, VariableNode*> VarList;

      public:
        StructVariableNode(VarList fieldVars);

      public:
        VariableNode* field(std::string fieldName);

      private:
        VarList fieldVars_;
    };

  } // namespace Shader
} // namespace Engine
