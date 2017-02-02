#include <scene/visitor/update-visitor.hpp>

namespace Engine
{
  namespace Scene
  {
    UpdateVisitor::UpdateVisitor()
      : deltaTime_{0.0f}
    {}

    void
    UpdateVisitor::visit(Node::NodePtr node)
    {
      auto t = node->component<Transform>();
      if (t != nullptr)
      {
        auto parentNode = node->getParent();
        while (parentNode)
        {
          auto parentTransform = parentNode->component<Transform>();

          t->setParentTransform(parentTransform);
          t->computeWorldMatrix();

          if (parentTransform) break;

          parentNode = parentNode->getParent();
        }
      }

      // Calls all registered update callbacks
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
