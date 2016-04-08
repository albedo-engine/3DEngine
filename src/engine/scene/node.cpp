#include "node.hpp"

namespace Engine
{
  namespace Scene
  {
    Node::Node()
      : name_("")
    { }

    Node::Node(const std::string& name)
      : name_(name)
    { }

    bool
    Node::add_child(Node::NodePtr n)
    {
      if (n->parent_ != nullptr || has_child(n))
        return false;

      // Puts the new child in the children container
      children_.push_back(n);
      // Updates the child's parent pointer to the current Node instance
      // Use the boost shared_from_this
    }

    bool
    Node::remove_child(Node::NodePtr n)
    {
      auto i = std::find(children_.begin(), children_.end(), n);
      if (i != children_.end())
      {
        children_.erase(i);
        return true;
      }
      else
        return false;
    }

    bool
    Node::has_child(Node::NodePtr n)
    {
      return std::find(children_.begin(), children_.end(), n) != children_.end();
    }

    void
    Node::clear_children()
    {
      children_.clear();
    }

    Node::NodePtr&
    Node::get_child_at(size_t i)
    {
      return children_.at(i);
    }

    Node::NodePtr&
    Node::get_parent()
    {
      return parent_;
    }

    bool
    Node::add_component(Component::ComponentPtr c)
    {
      if (has_component(c))
        return false;

      components_.push_back(c);
      return true;  
    }

    bool
    Node::remove_component(Component::ComponentPtr c)
    {
      auto i = std::find(components_.begin(), components_.end(), c);
      if (i == components_.end())
        return false;

      components_.erase(i);
      return true;
    }

    bool
    Node::has_component(Component::ComponentPtr c)
    {
      return std::find(components_.begin(), components_.end(), c) != components_.end();
    }

  } // namespace Scene
} // namespace Engine
