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
        const Rendering::Shader get_shader() const;

        const int& get_material_id() const;

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
        const GLchar* get_vertex_shader();
        const GLchar* get_fragment_shader();

      private:
        static int ID;

      private:
        Rendering::Shader shader_;
        AttributesMap     attributes_;
        int               material_id_;

    };
  } // namespace Component
} // namespace Engine
