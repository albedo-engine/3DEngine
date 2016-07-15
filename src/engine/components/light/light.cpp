#include "light.hpp"

namespace Engine
{
  namespace Components
  {
    Light::Light()
    {
      this->set_color(glm::vec3());
    }

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
      return store_.get<glm::vec3>("color");
    }

    void
    Light::set_color(glm::vec3 color)
    {
      store_.set<glm::vec3>("color", color);
    }

  } // Namespace Components
} // Namespace Engine