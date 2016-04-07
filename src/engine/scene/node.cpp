#include "node.hpp"

namespace scene
{
  Node::Node()
  { }

  Node::Node(std::string& name)
       : name_(name)
  { }

  bool
  Node::add_child(Node::NodePtr n)
  {
    if (parent_ != nullptr
        || std::find(children_.begin(), children_.end(), n) != children_.end())
      return false;

    // Puts the new child in the children container
    children_.push_back(n);
    // Updates the child's parent pointer to the current Node instance
    // Use the boost shared_from_this
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

} // namespace scene
