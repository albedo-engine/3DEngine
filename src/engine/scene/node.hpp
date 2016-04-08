#pragma once

#include "../../utils/headers/common.hpp"
#include "../components/component.hpp"

using namespace Engine::Components;

namespace Engine
{
  namespace Scene
  {
    class Node
    {
      public:
        typedef std::shared_ptr<Node>                 NodePtr;
        typedef std::vector<NodePtr>                  NodeList;
        typedef std::vector<Component::ComponentPtr>  ComponentList;

      public:
        Node();
        Node(const std::string& name);

      public:
        bool add_child(NodePtr n);
        bool remove_child(NodePtr n);
        bool has_child(NodePtr n);
        void clear_children();
        NodePtr& get_child_at(size_t i);
        NodePtr& get_parent();

        bool add_component(Component::ComponentPtr c);
        bool remove_component(Component::ComponentPtr c);
        bool has_component(Component::ComponentPtr c);
      private:
        const std::string   name_;
        NodePtr             parent_;
        NodeList            children_;
        ComponentList       components_;
    };
  } // namespace Scene
} // namespace Engine
