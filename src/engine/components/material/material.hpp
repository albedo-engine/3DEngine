#pragma once

#include <utils/headers/common.hpp>
#include <components/component.hpp>
#include <components/geometry/quad.hpp>
#include <rendering/shader.hpp>
#include <boost/variant.hpp>
#include <unordered_map>

namespace Engine
{
  namespace Components
  {
    class Material : public Component
    {
      public:
        typedef std::shared_ptr<Material>                         MaterialPtr;
        typedef boost::variant<glm::vec3, glm::mat4>            AttributeType;
        typedef std::unordered_map<std::string, AttributeType>  AttributesMap;

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

      public:
        void set_shader(Rendering::Shader::ShaderPtr shader);

      public:
        const Rendering::Shader::ShaderPtr get_shader() const;

        const GLuint& get_material_id() const;

      private:
        static GLuint ID;

      private:
        Rendering::Shader::ShaderPtr  shader_;
        AttributesMap                 attributes_;
        GLuint                        material_id_;

    };
  } // namespace Component
} // namespace Engine
