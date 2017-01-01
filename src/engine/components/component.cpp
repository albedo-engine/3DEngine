#include "component.hpp"

namespace Engine
{
  namespace Components
  {
    Component::~Component()
    { }

    void
    Component::setParent(Scene::Node::NodePtr target_node)
    {
      targetNode_ = target_node;
    }

    std::shared_ptr<Scene::Node>
    Component::getTarget()
    {
      return targetNode_.lock();
    }

  }
}
