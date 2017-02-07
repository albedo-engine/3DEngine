#include <scene/visitor/update-visitor.hpp>

namespace Engine
{
  namespace Scene
  {
    UpdateVisitor::UpdateVisitor()
    {}

    void
    UpdateVisitor::visit(Node::NodePtr node)
    {
      //
      // Pre-traversal
      //
      auto t = node->component<Transform>();
      if (t != nullptr)
      {
        this->computeNodeTransform(node, t);
      }

      // Calls all registered update callbacks
      for (const auto& callback : node->getUpdateCallbackList())
        callback(node);

      this->traverse(node);

      //
      // Post-traversal
      //
      if (t != nullptr)
        t->setDirty(false);
    }

    void
    UpdateVisitor::computeNodeTransform(Node::NodePtr node, Transform::TransformPtr transform)
    {
      auto parentNode = node->getParent();
      do
      {
        auto parentTransform = parentNode->component<Transform>();

        transform->computeWorldMatrix(parentTransform);
        if (parentTransform) break;

        parentNode = parentNode->getParent();
      } while (parentNode);
    }
  } // namespace Scene
} // namespace Engine
