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
        //this->computeNodeTransform(node, t);
        Transform::TransformPtr parentTransform = nullptr;
        if (!transformStack_.empty())
          parentTransform = transformStack_[transformStack_.size() - 1];
        t->computeWorldMatrix(parentTransform);

        transformStack_.push_back(t);
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

      if (!transformStack_.empty())
        transformStack_.pop_back();
    }
  } // namespace Scene
} // namespace Engine
