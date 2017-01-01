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
    Node::addChild(Node::NodePtr n)
    {
      if (n == nullptr)
        throw new std::logic_error("The node child cannot be null");
      else if (n == getParent())
        throw new std::logic_error("A parent node cannot be added as a child node");

      if (n->getParent())
        n->getParent()->removeChild(n);

      // Puts the new child in the children container
      children_.push_back(n);
      // Updates the child's parent pointer to the current Node instance
      n->parent_ = shared_from_this();

      return true;
    }

    bool
    Node::removeChild(Node::NodePtr n)
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

    void
    Node::clearChildren()
    {
      children_.clear();
    }

    Node::NodePtr
    Node::getParent()
    {
      return parent_.lock();
    }

    const Node::NodeList&
    Node::getChildren() const
    {
      return children_;
    }

    bool
    Node::hasChild(Node::NodePtr n)
    {
      return std::find(children_.begin(), children_.end(), n) != children_.end();
    }

    bool
    Node::addComponent(Component::ComponentPtr c)
    {
      if (hasComponent(c))
        throw new std::logic_error("This component instance is already contained in the node");

      c->setParent(shared_from_this());
      components_.push_back(c);
      return true;
    }

    bool
    Node::removeComponent(Component::ComponentPtr c)
    {
      auto i = std::find(components_.begin(), components_.end(), c);
      if (i == components_.end())
        return false;

      c->setParent(nullptr);
      components_.erase(i);
      return true;
    }

    bool
    Node::hasComponent(Component::ComponentPtr c)
    {
      return std::find(components_.begin(), components_.end(), c) != components_.end();
    }

  } // namespace Scene
} // namespace Engine
