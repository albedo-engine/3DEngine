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
    class Material
      : public Component, public std::enable_shared_from_this<Material>
    {
      public:
        typedef std::shared_ptr<Material> MaterialPtr;

      public:
        Material();
        ~Material();

      public:
        bool
        unique() override;

      public:
        void
        sendUniforms();

      public:
        /** \brief Set the pointer to the actual shader using this material.
         *
         * \param shader
         * the pointer to the shader using this material.
         */
        void
        setShader(const Rendering::Shader::ShaderPtr& shader);

      public:
        const Rendering::Shader::ShaderPtr&
        getShader() const;

        const GLuint&
        getMaterialId() const;

        const Data::Store::StorePtr&
        getStore() const;

      protected:
        Rendering::Shader::ShaderPtr  shader_;
        GLuint                        materialId_;
        Data::Store::StorePtr         store_;

      private:
        static GLuint ID;

    };
  } // namespace Component
} // namespace Engine
