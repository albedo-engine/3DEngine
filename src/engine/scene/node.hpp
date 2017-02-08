#pragma once

#include <components/component.hpp>
#include <scene/visitor/visitor.hpp>

namespace Engine
{
  namespace Scene
  {
    using namespace Engine::Components;

    class Node : public std::enable_shared_from_this<Node>
    {
      public:
        typedef std::shared_ptr<Node>                     NodePtr;
        typedef std::vector<NodePtr>                      NodeList;
        typedef std::vector<Component::ComponentPtr>      ComponentList;
        typedef std::vector<std::function<bool(NodePtr)>> UpdateCallbackList;

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
        void
        accept(std::shared_ptr<NodeVisitor> visitor);

      public:

        // TODO: Overload using initializer_list to add several nodes in a row
        bool
        addChild(NodePtr n);

        bool
        removeChild(NodePtr n);

        void
        clearChildren();

        bool
        addComponent(Component::ComponentPtr c);

        bool
        removeComponent(Component::ComponentPtr c);

        bool
        addUpdateCallback(std::function<bool(NodePtr)> callback);

      public:
        const std::string&
        getName() const;

        NodePtr
        getParent();

        const NodeList&
        getChildren() const;

        bool
        hasChild(NodePtr n);

        bool
        hasComponent(Component::ComponentPtr c);

        template<typename T>
        std::shared_ptr<T> component() const
        {
          std::shared_ptr<T> result_ptr = nullptr;
          auto               result_it  =
                               std::find_if(components_.begin(),
                                            components_.end(),
                                            [&result_ptr](
                                              const Component::ComponentPtr& e)
                                            {
                                              result_ptr = std::dynamic_pointer_cast<T>(
                                                e);
                                              return (result_ptr != nullptr);
                                            });
          return (result_it != components_.end()) ? result_ptr : nullptr;
        }

        const UpdateCallbackList&
        getUpdateCallbackList() const;

      private:
        const std::string   name_;
        std::weak_ptr<Node> parent_;
        NodeList            children_;

        ComponentList components_;

        UpdateCallbackList updateCallbackList_;
    };
  } // namespace Scene
} // namespace Engine
