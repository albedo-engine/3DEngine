#include "component.hpp"

namespace Engine
{
  namespace Components
  {
    Component::~Component()
    { }

    void
    Component::set_parent(Scene::Node::NodePtr parent)
    {
      parent_ = parent;
    }
  }
}
