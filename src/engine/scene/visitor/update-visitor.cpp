#include <scene/visitor/update-visitor.hpp>

namespace Engine
{
  namespace Scene
  {
    void
    UpdateVisitor::visit(Node::NodePtr node)
    {
      for (const auto& callback : node->getUpdateCallbackList())
        callback(node);

      this->traverse(node);
    }

    void UpdateVisitor::setDeltaTime(float deltaTime)
    {
      deltaTime_ = deltaTime;
    }

  } // namespace Scene
} // namespace Engine