#include "component-factory.hpp"

namespace Engine
{
  namespace Components
  {
    Data::DataContainer& ComponentFactory::get_data_container()
    {
      return data_container_;
    }

    /*template<>
    Material::MaterialPtr
    ComponentFactory::component<Material>()
    {
      auto component_ptr = get_component_ptr<Material>();
      auto& material_list = data_container_.get<Material::MaterialPtr>();
      material_list.push_back(component_ptr);

      return component_ptr;
    }*/


    /*template<>
    PointLight::PointLightPtr
    ComponentFactory::component<PointLight>()
    {
      auto component_ptr = get_component_ptr<PointLight>();
      auto& material_list = data_container_.get<Light::LightPtr>();
      material_list.push_back(component_ptr);

      return component_ptr;
    }*/

  } // namespace Components
} // namespace Engine