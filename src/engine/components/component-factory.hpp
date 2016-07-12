//
// Created by david on 09/07/16.
//

#pragma once

#include <memory>
#include <data/data-container.hpp>
#include <data/singleton.hpp>
#include <components/material/material.hpp>

namespace Engine
{
  namespace Components
  {
    class ComponentFactory : public Singleton<ComponentFactory>
    {
      public:
        template<typename T>
        std::shared_ptr<T>
        component()
        {
          return get_component_ptr<T>();
        }

      private:
        template<typename T>
        std::shared_ptr<T>
        get_component_ptr()
        {
          return std::make_shared<T>();
        }

      private:
        Data::DataContainer data_container_;
    };

    template<>
    Material::MaterialPtr
    ComponentFactory::component<Material>()
    {
      auto component_ptr = get_component_ptr<Material>();
      data_container_.get_list<Material::MaterialPtr>().push_back(component_ptr);

      return component_ptr;
    }

  } // namespace Components
} // namespace Engine
