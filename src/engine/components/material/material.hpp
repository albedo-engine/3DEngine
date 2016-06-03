#pragma once

#include <utils/headers/common.hpp>
#include <components/component.hpp>
#include <components/geometry/quad.hpp>
#include <rendering/shader.hpp>

namespace Engine
{
  namespace Components
  {
    class Material : public Component
    {
      public:
        typedef std::shared_ptr<Material>  MaterialPtr;

      public:
        MaterialPtr
        static inline
        create()
        {
          return std::make_shared<Material>();
        }

      public:
        Material();
        ~Material();

      public:
        bool unique() override;

        const Rendering::Shader get_shader() const;

      private:
        const GLchar* get_vertex_shader();
        const GLchar* get_fragment_shader();

      private:
        Rendering::Shader shader_;

    };
  } // namespace Component
} // namespace Engine
