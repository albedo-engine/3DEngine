#pragma once

#include <memory>
#include <string>
#include <vector>
#include <algorithm>

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
      bool add_child(NodePtr n);
      void clear_children();
      NodePtr& get_child_at(size_t i);
      NodePtr& get_parent();

    private:
      std::string   name_;
      NodePtr       parent_;
      NodeList      children_;
  };

 } // namespace scene
