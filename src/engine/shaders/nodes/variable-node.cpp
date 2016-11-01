#include "variable-node.hpp"

namespace Engine
{
  namespace Shader
  {

    /**
     * VariableNode class
     */

    std::string
    VariableNode::toString()
    {
      return name_;
    }

    void
    VariableNode::setName(std::string name)
    {
      name_ = name;
    }

    VariableNode*
    VariableNode::field(std::string fieldName)
    {
      return this;
    }

    void
    VariableNode::setType(std::string type)
    {
      type_ = type;
    }

    void
    VariableNode::setPrefix(std::string prefix)
    {
      prefix_ = prefix;
    }

    const std::string
    VariableNode::getName() const
    {
      return name_;
    }

    const std::string
    VariableNode::getType() const
    {
      return type_;
    }

    const std::string
    VariableNode::getPrefix() const
    {
      return prefix_;
    }

    /**
     * StructVariableNode class
     */

    VariableNode*
    StructVariableNode::field(std::string fieldName)
    {
      auto elt = fieldVars_.find(fieldName);
      if (elt == fieldVars_.end())
      {
        throw std::logic_error("ShaderNode: the StructVariableNode "
                               "does not contains this field");
      }

      return elt->second;
    }

    void
    StructVariableNode::init(VarList varList)
    {
      fieldVars_ = varList;
    }

  } // namespace Shader
} // namespace Engine
