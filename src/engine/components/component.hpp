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
        typedef std::shared_ptr<Component>    ComponentPtr;

      public:
        virtual ~Component();

        void
        set_parent(std::shared_ptr<Scene::Node> parent);

      protected:
        std::shared_ptr<Scene::Node> parent_;

    };
  } // namespace Components
} // namespace Engine

#include <scene/node.hpp>