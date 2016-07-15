#pragma once

#include <utils/headers/common.hpp>
#include <components/component.hpp>
#include <components/geometry/quad.hpp>
#include <rendering/shader.hpp>
#include <data/store.hpp>

namespace Engine
{
  namespace Components
  {
    /** \class Material
     *
     * \brief Link between an actual shader and its data, contained in a Store.
     */
    class Material : public Component
    {
      public:
        typedef std::shared_ptr<Material> MaterialPtr;

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
        /** \brief Set the pointer to the actual shader using this material.
         *
         * \param shader
         * the pointer to the shader using this material.
         */
        void set_shader(Rendering::Shader::ShaderPtr shader);

      public:
        const Rendering::Shader::ShaderPtr get_shader() const;

        const GLuint& get_material_id() const;

        const Data::Store::StorePtr get_store() const;

      private:
        static GLuint ID;

      private:
        Rendering::Shader::ShaderPtr  shader_;
        GLuint                        material_id_;
        Data::Store::StorePtr         store_;

    };
  } // namespace Component
} // namespace Engine
