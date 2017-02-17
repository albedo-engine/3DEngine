#include "light.hpp"

namespace Engine
{
  namespace Components
  {
    Light::Light()
    {
      this->store_ = Data::Store::create();
      this->setColor(glm::vec3());
    }

    Light::~Light()
    { }

    bool
    Light::unique()
    {
      return true;
    }

    const glm::vec3&
    Light::getColor() const
    {
      return *store_->get<glm::vec3>("color");
    }

    void
    Light::setColor(const glm::vec3 color)
    {
      store_->set<glm::vec3>("color", color);
    }

  } // Namespace Components
} // Namespace Engine
