#pragma once

#include "../../utils/headers/common.hpp"
#include "../scene/node.hpp"

namespace Engine
{
  namespace Components
  {
    class Component
    {
      public:
        typedef std::shared_ptr<Component>    ComponentPtr;

      public:
        Component(Scene::Node::NodePtr parent_node);
        virtual ~Component();

    protected:
      Scene::Node::NodePtr parent_;

    };
  } // namespace Component
} // namespace Engine
