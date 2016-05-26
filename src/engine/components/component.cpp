#include "component.hpp"

namespace Engine
{
  namespace Components
  {
    Component::Component(Scene::Node::NodePtr parent)
              : parent_(parent)
    { }

    Component::~Component()
    { }
  }
}
