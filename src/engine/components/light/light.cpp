#include "light.hpp"

namespace Engine
{
  namespace Components
  {
    Light::Light()
    { }

    Light::~Light()
    { }

    bool
    Light::unique()
    {
      return true;
    }

    const glm::vec3&
    Light::get_color() const
    {
      return color_;
    }

    void
    Light::set_color(glm::vec3 color)
    {
      color_ = color;
    }

  } // Namespace Components
} // Namespace Engine