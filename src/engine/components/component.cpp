#include "component.hpp"

namespace Engine
{
  namespace Components
  {
    Component::~Component()
    { }

    void
    Component::set_parent(Scene::Node::NodePtr target_node)
    {
      target_node_ = target_node;
    }

  }
}
