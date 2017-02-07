#pragma once

#include <scene/visitor/visitor.hpp>

#include <components/transform/transform.hpp>

namespace Engine
{
  namespace Scene
  {
    class UpdateVisitor : public NodeVisitor
    {
      public:
        typedef std::shared_ptr<UpdateVisitor> UpdateVisitorPtr;

      public:
        UpdateVisitorPtr
        static inline
        create()
        {
          return std::make_shared<UpdateVisitor>();
        }

      public:
        UpdateVisitor();

      public:
        virtual void
        visit(std::shared_ptr<Node> node) override;

      public:
        void
        setDeltaTime(float deltaTime);

    private:
        void
        computeNodeTransform(Node::NodePtr node, Transform::TransformPtr transform);

    };
  } // namespace Scene
} // namespace Engine
