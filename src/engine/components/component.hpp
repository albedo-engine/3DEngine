#pragma once

#include <utils/headers/common.hpp>

namespace Engine
{
  namespace Scene
  {
    class Node;
  }
  namespace Components
  {
    class Component
    {
      public:
        typedef std::shared_ptr<Component> ComponentPtr;

      public:
        virtual ~Component();

      public:
        virtual bool
        unique() = 0;

      public:
        void
        setParent(const std::shared_ptr<Scene::Node>& parent);

      public:
        std::shared_ptr<Scene::Node>
        getTarget();

      private:
        std::weak_ptr<Scene::Node> targetNode_;

    };
  } // namespace Components
} // namespace Engine

#include <scene/node.hpp>
