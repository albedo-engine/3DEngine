#include "component-factory.hpp"


namespace Engine
{
  namespace Components
  {
    Data::DataContainer& ComponentFactory::get_data_container()
    {
      return data_container_;
    }
  } // namespace Components
} // namespace Engine