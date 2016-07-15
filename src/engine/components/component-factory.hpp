#pragma once

#include <memory>
#include <data/data-container.hpp>
#include <data/singleton.hpp>
#include <components/material/material.hpp>
#include <components/light/pointlight.hpp>

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

        Data::DataContainer& get_data_container();

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

    // TODO: Factorize the specilization code using a common function
    template<>
    Material::MaterialPtr
    ComponentFactory::component<Material>()
    {
      auto component_ptr = get_component_ptr<Material>();
      auto& material_list = data_container_.get<Material::MaterialPtr>();
      material_list.push_back(component_ptr);

      return component_ptr;
    }

    // TODO: Fix the template specialization using boost (enable_if, is_base_of)
    template<>
    PointLight::PointLightPtr
    ComponentFactory::component<PointLight>()
    {
      auto component_ptr = get_component_ptr<PointLight>();
      auto& material_list = data_container_.get<Light::LightPtr>();
      material_list.push_back(component_ptr);

      return component_ptr;
    }

  } // namespace Components
} // namespace Engine
