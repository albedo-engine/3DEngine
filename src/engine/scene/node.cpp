#include "node.hpp"

namespace scene
{
  Node::Node()
  { }

  Node::Node(std::string& name)
       : name_(name)
  { }

  void
  Node::add_child(Node::NodePtr n)
  {
    children_.push_back(n);
  }

  void
  Node::clear_children()
  {
    children_.clear();
  }

  Node::NodePtr&
  Node::get_child_at(size_t i)
  {
    children_.at(i);
  }

} // namespace scene
