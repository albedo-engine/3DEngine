#pragma once

#include "../engine.hpp"

namespace scene
{
  class Node
  {
    public:
      typedef std::shared_ptr<Node>               NodePtr;
      typedef std::vector<std::shared_ptr<Node>>  NodeList;

    public:
      Node();
      Node(std::string& name);

    public:
      void add_child(NodePtr n);
      NodePtr& get_child_at(size_t i);
      void clear_children();

    private:
      std::string   name_;
      NodeList      children_;

  };

} // namespace scene
