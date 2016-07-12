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

        template <typename T>
        const AttributeType& get_attribute(std::string attribute_name)
        {
          return boost::get<T>(attributes_[attribute_name]);
        }

        template <typename T>
        void set_attribute(std::string attribute_name, T value)
        {
          attributes_[attribute_name] = value;
        }

      private:
        static GLuint ID;

      private:
        Rendering::Shader::ShaderPtr  shader_;
        AttributesMap                 attributes_;
        GLuint                        material_id_;

    };
  } // namespace Component
} // namespace Engine
