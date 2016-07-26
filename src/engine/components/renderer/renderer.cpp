#include "renderer.hpp"
#include <iostream>
#include <components/component-factory.hpp>

namespace Engine
{
  namespace Components
  {
    Renderer::Renderer(Scene::Node::NodePtr camera, int width, int height)
            : renderWidth_(width)
            , renderHeight_(height)
            , camera_(camera->component<Camera>())
            , gBufferShader_(
                    Rendering::Shader(
                            GET_SHADER(gbuffer_vs),
                            GET_SHADER(gbuffer_fs)))
            , deferredShader_(
                    Rendering::Shader(
                            GET_SHADER(deferred_vs),
                            GET_SHADER(deferred_fs)))
            , renderQuad_(Components::Quad::create())
    {
      if (!camera_)
        throw std::invalid_argument("Camera node doesn't contain a camera component.");

      if (!gBufferShader_.compile())
        throw std::logic_error("gBuffer shader compilation error "
                               + std::string(gBufferShader_.get_compilation_info()));

      if (!deferredShader_.compile())
        throw std::logic_error("deferred shader compilation error "
                               + std::string(deferredShader_.get_compilation_info()));


      deferredShader_.use_shader();
      glUniform1i(glGetUniformLocation(deferredShader_.get_program(), "position"), 0);
      glUniform1i(glGetUniformLocation(deferredShader_.get_program(), "normal"), 1);
      glUniform1i(glGetUniformLocation(deferredShader_.get_program(), "albedo"), 2);


      // Create the FBO
      glGenFramebuffers(1, &gFrameBuffer_);
      glBindFramebuffer(GL_FRAMEBUFFER, gFrameBuffer_);

      // gBuffer Textures
      glGenTextures(3, gTextures);
      for (unsigned int i = 0; i < 3; i++)
      {
        glBindTexture(GL_TEXTURE_2D, gTextures[i]);

        if (i == 2) // Diffuse
          glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, renderWidth_, renderHeight_,
                       0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        else
          glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, renderWidth_, renderHeight_,
                       0, GL_RGB, GL_FLOAT, NULL);

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i,
                               GL_TEXTURE_2D, gTextures[i], 0);
      }

      // Depth
      glGenTextures(1, &gDepthTexture);
      glBindTexture(GL_TEXTURE_2D, gDepthTexture);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, renderWidth_,
                   renderHeight_, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
      glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                             GL_TEXTURE_2D, gDepthTexture, 0);

      GLenum DrawBuffers[] = {GL_COLOR_ATTACHMENT0,
                              GL_COLOR_ATTACHMENT1,
                              GL_COLOR_ATTACHMENT2};
      glDrawBuffers(3, DrawBuffers);

      GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

      if (Status != GL_FRAMEBUFFER_COMPLETE)
        throw std::logic_error("gBuffer framebuffer error.");

      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    }

    Renderer::~Renderer()
    {

    }

    bool
    Renderer::unique()
    {
      return false;
    }

    void
    Renderer::toggle_debug(unsigned int options)
    {
      debugOptions_ = options;
    }


    void
    Renderer::render()
    {
      glPolygonMode(GL_FRONT_AND_BACK,
                    (debugOptions_ & WIREFRAME_MODE) ? GL_LINE : GL_FILL);

      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, gFrameBuffer_);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      gBufferShader_.use_shader();
      render_geometry(get_target());

      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

      render_lights();

      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
      glBindFramebuffer(GL_READ_FRAMEBUFFER, gFrameBuffer_);
      if (debugOptions_ > 0)
        debug_display();
    }

    void
    Renderer::display()
    {
      render();

      glBindVertexArray(renderQuad_->get_vao());
      glDrawElements(GL_TRIANGLES, (GLsizei)renderQuad_->get_indices().size(), GL_UNSIGNED_INT, 0);
      glBindVertexArray(0);
    }

    void
    Renderer::render_geometry(Scene::Node::NodePtr node)
    {
      for (Scene::Node::NodePtr child : node->get_children())
      {
        Geometry::GeometryPtr geometry = child->component<Geometry>();
        Transform::TransformPtr transform = child->component<Transform>();

        if (geometry && transform)
        {
          GLuint program = gBufferShader_.get_program();
          GLint modelUni = glGetUniformLocation(program, "model");
          GLint viewUni = glGetUniformLocation(program, "view");
          GLint projectionUni = glGetUniformLocation(program, "projection");

          // View matrix
          glUniformMatrix4fv(viewUni, 1, GL_FALSE,
                             glm::value_ptr(camera_->get_view_matrix()));
          // Projection matrix
          glUniformMatrix4fv(projectionUni, 1, GL_FALSE,
                             glm::value_ptr(camera_->get_projection_matrix()));
          // Model matrix
          glUniformMatrix4fv(modelUni, 1, GL_FALSE,
                             glm::value_ptr(transform->get_world_matrix()));

          // Render
          glBindVertexArray(geometry->get_vao());
          glDrawElements(GL_TRIANGLES, (GLsizei)geometry->get_indices().size(),
                         GL_UNSIGNED_INT, 0);
          glBindVertexArray(0);
        }

        render_geometry(child);
      }
    }

    // TODO: Use stored light vector instead for performance and cache efficency
    void
    Renderer::build_lights_vector(std::vector<Scene::Node::NodePtr>& vec, Scene::Node::NodePtr node)
    {
      for (Scene::Node::NodePtr child : node->get_children())
      {
        if (child->component<Light>())
          vec.push_back(child);
      }
    }

    void
    Renderer::render_lights()
    {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      deferredShader_.use_shader();

      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, gTextures[0]);
      glActiveTexture(GL_TEXTURE1);
      glBindTexture(GL_TEXTURE_2D, gTextures[1]);
      glActiveTexture(GL_TEXTURE2);
      glBindTexture(GL_TEXTURE_2D, gTextures[2]);

      /*std::vector<Scene::Node::NodePtr> lights_vec;
      build_lights_vector(lights_vec, get_target());*/

      auto& lights_vec = ComponentFactory::instance()
                          ->get_data_container().get<Light::LightPtr>();

      int idx = 0;
      for (auto lights : lights_vec)
      {
        glm::vec3 light_colors = lights->get_color();
        glUniform3fv(
                glGetUniformLocation(deferredShader_.get_program(),
                                     ("lights[" + std::to_string(idx) + "].Position").c_str()),
                1,
                &lights->get_target()->component<Transform>()->get_world_position()[0]);
        glUniform3fv(
                glGetUniformLocation(deferredShader_.get_program(),
                                     ("lights[" + std::to_string(idx) + "].Color").c_str()),
                1,
                &light_colors[0]);

        // TODO: Improve these hardcoded constants
        const GLfloat constant = 1.0;
        const GLfloat linear = 0.7;
        const GLfloat quadratic = 1.8;
        glUniform1f(
                glGetUniformLocation(deferredShader_.get_program(),
                                     ("lights[" + std::to_string(idx) + "].Linear").c_str()),
                linear);
        glUniform1f(
                glGetUniformLocation(deferredShader_.get_program(),
                                     ("lights[" + std::to_string(idx) + "].Quadratic").c_str()),
                quadratic);

        // Sphere radius computation
        const GLfloat lightThreshold = 5.0; // 5 / 256
        const GLfloat maxBrightness = std::fmaxf(
                std::fmaxf(light_colors.r, light_colors.g),
                light_colors.b);

        GLfloat radius =
                (-linear + static_cast<float>(
                        std::sqrt(
                                linear * linear -
                                4 * quadratic * (constant - (256.0 / lightThreshold) * maxBrightness))
                ))
                / (2 * quadratic);
        glUniform1f(
                glGetUniformLocation(deferredShader_.get_program(),
                                     ("lights[" + std::to_string(idx) + "].Radius").c_str()),
                radius);
        idx++;
      }

      glUniform3fv(
              glGetUniformLocation(deferredShader_.get_program(),
                                   "viewPos"),
              1,
              &camera_->get_target()->component<Transform>()->get_world_position()[0]);
    }


    void
    Renderer::debug_display()
    {
      GLint width = (GLint)(renderWidth_ / 5.0f);
      GLint height = (GLint)(renderHeight_ / 5.0f);

      unsigned int i = 0;
      if (debugOptions_ & SHOW_POSITION_BUFFER)
      {
        glReadBuffer(GL_COLOR_ATTACHMENT0);
        debug_display_framebuffer(width, height, i++);
      }

      if (debugOptions_ & SHOW_NORMAL_BUFFER)
      {
        glReadBuffer(GL_COLOR_ATTACHMENT1);
        debug_display_framebuffer(width, height, i++);
      }

      if (debugOptions_ & SHOW_DIFFUSE_BUFFER)
      {
        glReadBuffer(GL_COLOR_ATTACHMENT2);
        debug_display_framebuffer(width, height, i++);
      }
    }

    void
    Renderer::debug_display_framebuffer(GLint width, GLint height,
                                        unsigned int position)
    {
      glBlitFramebuffer(0, 0, renderWidth_, renderHeight_,
                        0, renderHeight_ - height * (position + 1),
                        width, renderHeight_ - height * position,
                        GL_COLOR_BUFFER_BIT, GL_LINEAR);
    }

  } // namespace Components
} // namespace Engine
