#pragma once

#include <memory>
#include <vector>
#include <boost/variant.hpp>

#include <components/material/material.hpp>
#include <components/light/light.hpp>
#include <components/light/pointlight.hpp>

#include "data-container.hpp"
#include "singleton.hpp"

namespace Engine
{
  namespace Data
  {
    template <typename ... DataTypes>
    class DataContainerType
    {
      public:
        using DataListContainer = std::tuple<std::vector<DataTypes>...>;

      public:
        template<typename DataType>
        std::vector<DataType>&
        get()
        {
          return std::get<std::vector<DataType>>(data_);
        }

      private:
        DataListContainer data_;
    };

    using DataContainer = DataContainerType<Components::Material::MaterialPtr,
      Components::Light::LightPtr>;
  } // namespace Data
} // namespace Engine
