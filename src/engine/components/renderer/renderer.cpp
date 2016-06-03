#include "renderer.hpp"

namespace Engine
{
  namespace Components
  {
    Renderer::Renderer(Scene::Node::NodePtr camera, int width, int height)
            : renderWidth_(width)
            , renderHeight_(height)
            , camera_(camera->component<Camera>())
            , quadShader_(
                    Rendering::Shader::createFromStrings(
                            get_quad_vertex_shader(),
                            get_quad_fragment_shader()))
    {
      if (!camera_)
        throw std::invalid_argument(
                "Camera node doesn't contain a camera component.");

      if (!quadShader_.compile())
        throw std::logic_error("Quad shader " + std::string(
                quadShader_.get_compilation_info()));

      quadGeometry_ = Components::Quad::create();

      glGenFramebuffers(1, &frameBuffer_);
      glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer_);

      glGenTextures(1, &renderTexture_);
      glBindTexture(GL_TEXTURE_2D, renderTexture_);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, renderWidth_, renderHeight_, 0,
                   GL_RGB, GL_UNSIGNED_BYTE, 0);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glBindTexture(GL_TEXTURE_2D, 0);
      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                             GL_TEXTURE_2D, renderTexture_, 0);

      glGenRenderbuffers(1, &renderBuffer_);
      glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer_);
      glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8,
                            renderWidth_, renderHeight_);
      glBindRenderbuffer(GL_RENDERBUFFER, 0);

      glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                                GL_RENDERBUFFER, renderBuffer_);

      if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        throw std::logic_error("Framebuffer initialization error");

      glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    Renderer::~Renderer()
    {
      glDeleteFramebuffers(1, &frameBuffer_);
      glDeleteTextures(1, &renderTexture_);
      glDeleteRenderbuffers(1, &renderBuffer_);
    }

    bool
    Renderer::unique()
    {
      return false;
    }

    const GLchar*
    Renderer::get_quad_vertex_shader()
    {
      return "#version 330 core\n"
              "layout (location = 0) in vec3 position;\n"
              "layout (location = 1) in vec3 normal;\n"
              "layout (location = 2) in vec2 texCoords;\n"
              "\n"
              "out vec2 TexCoords;\n"
              "\n"
              "void main()\n"
              "{\n"
              "    gl_Position = vec4(position.x, position.y, position.z, 1.0f);\n"
              "    TexCoords = texCoords;\n"
              "}\n\0";
    }

    const GLchar*
    Renderer::get_quad_fragment_shader()
    {
      return "#version 330 core\n"
              "in vec2 TexCoords;\n"
              "out vec4 color;\n"
              "\n"
              "uniform sampler2D screenTexture;\n"
              "\n"
              "void main()\n"
              "{ \n"
              "    color = texture(screenTexture, TexCoords);\n"
              "}\n\0";
    }

    void
    Renderer::render(Scene::Node::NodePtr node)
    {
      for (Scene::Node::NodePtr child : node->get_children())
      {
        Geometry::GeometryPtr geometry = child->component<Geometry>();
        Transform::TransformPtr transform = child->component<Transform>();
        Material::MaterialPtr material = child->component<Material>();
        if (geometry && material && transform)
        {
          material->get_shader().use_shader();
          GLuint program = material->get_shader().get_program();

          // Hardcoded view till the camera view works
          glm::mat4 view;
          view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

          GLint modelUni = glGetUniformLocation(program, "model");
          GLint viewUni = glGetUniformLocation(program, "view");
          GLint projectionUni = glGetUniformLocation(program, "projection");

          glUniformMatrix4fv(viewUni, 1, GL_FALSE, glm::value_ptr(view));
          glUniformMatrix4fv(projectionUni, 1, GL_FALSE,
                             glm::value_ptr(camera_->get_projection_matrix()));

          // Hardcoded worl matrix till the transformation works
          //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(
          //        transform->get_world_position()));
          glm::mat4 model;
          model = glm::rotate(model, 1.f, glm::vec3(1));
          glUniformMatrix4fv(modelUni, 1, GL_FALSE, glm::value_ptr(model));

          // Render
          glBindVertexArray(geometry->get_vao());
          glDrawElements(GL_TRIANGLES, (GLsizei)geometry->get_indices().size(),
                         GL_UNSIGNED_INT, 0);
          glBindVertexArray(0);
        }

        render(child);
      }
    }

    void
    Renderer::display()
    {
      glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer_);

      glClearColor(1.0f, 0.0f, 0.0f, 1.0f); //R - Quad
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      render(get_target());

      glBindFramebuffer(GL_FRAMEBUFFER, 0);
      glClearColor(0.0f, 0.0f, 1.0f, 1.0f); //B - Screen
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      quadShader_.use_shader();
      glBindVertexArray(quadGeometry_->get_vao());
      glBindTexture(GL_TEXTURE_2D, renderTexture_);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

      glBindVertexArray(0);
    }

  } // namespace Components
} // namespace Engine
