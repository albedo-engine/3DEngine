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
        virtual ~Component();

        void
        set_parent(Scene::Node::NodePtr parent);

      protected:
        Scene::Node::NodePtr parent_;

    };
  } // namespace Components
} // namespace Engine
