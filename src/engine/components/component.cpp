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

    std::shared_ptr<Scene::Node>
    Component::get_target()
    {
      return target_node_.lock();
    }

  }
}
