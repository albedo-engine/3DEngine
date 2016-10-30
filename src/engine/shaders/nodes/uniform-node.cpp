#include "uniform-node.hpp"

namespace Engine
{
  namespace Shader
  {
    std::string
    UniformNode::toString()
    {
      return name_;
    }

    void
    UniformNode::setType(std::string type)
    {
      type_ = type;
    }

    const
    std::string UniformNode::getType() const
    {
      return type_;
    }

    void
    UniformNode::setDefaultValue(std::string value)
    {
      defaultValue_ = value;
    }

    const
    std::string UniformNode::getDefaultValue() const
    {
      return defaultValue_;
    }

    void
    UniformNode::setName(std::string name)
    {
      name_ = name;
    }

    const
    std::string UniformNode::getName() const
    {
      return name_;
    }
  } // namespace Shader
} // namespace Engine