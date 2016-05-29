#pragma once

#include <components/component.hpp>

namespace Engine
{
  namespace Scene
  {
    using namespace Engine::Components;

    class Node : public std::enable_shared_from_this<Node>
    {
      public:
        typedef std::shared_ptr<Node>                 NodePtr;
        typedef std::vector<NodePtr>                  NodeList;
        typedef std::vector<Component::ComponentPtr>  ComponentList;

      public:
        NodePtr
        static inline
        create()
        {
          return std::make_shared<Node>();
        }

        NodePtr
        static inline
        create(const std::string& name)
        {
          return std::make_shared<Node>(name);
        }

      public:
        Node();
        Node(const std::string& name);

      public:
        bool add_child(NodePtr n);
        bool remove_child(NodePtr n);
        void clear_children();

        bool add_component(Component::ComponentPtr c);
        bool remove_component(Component::ComponentPtr c);

      public:
        bool has_child(NodePtr n);
        NodePtr& get_child_at(size_t i);
        NodePtr& get_parent();

        bool has_component(Component::ComponentPtr c);
        template<typename T>
        std::shared_ptr<T> component() const
        {
          std::shared_ptr<T> result_ptr = nullptr;
          auto result_it = std::find_if(components_.begin(), components_.end(),
                                      [&result_ptr](const Component::ComponentPtr& e)
                                      {
                                        result_ptr = std::dynamic_pointer_cast<T>(e);
                                        return (result_ptr != nullptr);
                                      });
          return (result_it != components_.end()) ? result_ptr : nullptr;
        }

      private:
        const std::string   name_;
        NodePtr             parent_;
        NodeList            children_;
        ComponentList       components_;
    };
  } // namespace Scene
} // namespace Engine
