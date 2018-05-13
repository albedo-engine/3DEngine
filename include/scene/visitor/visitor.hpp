#pragma once

namespace Engine
{
  namespace Scene
  {
    class Node;
    class NodeVisitor : public std::enable_shared_from_this<NodeVisitor>
    {
      public:
        virtual void
        visit(std::shared_ptr<Node> node) = 0;

        void
        traverse(std::shared_ptr<Node> node);
    };
  } // namespace Scene
} // namespace Engine

#include <scene/node.hpp>
