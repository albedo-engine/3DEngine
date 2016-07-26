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
        typename std::enable_if<!std::is_base_of<Light, T>::value
                                && !std::is_base_of<Material, T>::value,
                                std::shared_ptr<T>
                                >::type
        component()
        {
          return get_component_ptr<T>();
        }

        template<typename T>
        typename std::enable_if<std::is_base_of<Light, T>::value
                                && !std::is_base_of<Material, T>::value,
                                std::shared_ptr<T>
                                >::type
        component()
        {
          auto component_ptr = get_component_ptr<T>();
          auto& material_list = data_container_.get<Light::LightPtr>();
          material_list.push_back(component_ptr);

          return component_ptr;
        };

        template<typename T>
        typename std::enable_if<!std::is_base_of<Light, T>::value
                                && std::is_base_of<Material, T>::value,
                                std::shared_ptr<T>
                                >::type
        component()
        {
          auto component_ptr = get_component_ptr<T>();
          auto& material_list = data_container_.get<Material::MaterialPtr>();
          material_list.push_back(component_ptr);

          return component_ptr;
        };

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

    // TODO: Factorize the specialization code using a common function
    /*template<>
    Material::MaterialPtr
    ComponentFactory::component<Material>();*/

    // TODO: Fix the template specialization using boost (enable_if, is_base_of)
    // TODO: in order to support every derived type easily
    /*template<>
    PointLight::PointLightPtr
    ComponentFactory::component<PointLight>();*/

  } // namespace Components
} // namespace Engine
