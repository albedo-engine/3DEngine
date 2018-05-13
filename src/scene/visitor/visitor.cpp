#include <scene/visitor/visitor.hpp>

namespace Engine
{
  namespace Scene
  {
    void
    NodeVisitor::traverse(std::shared_ptr<Node> node)
    {
      for (auto& child : node->getChildren())
      {
        child->accept(shared_from_this());
      }
    }
  } // namespace Scene
} // namespace Engine
