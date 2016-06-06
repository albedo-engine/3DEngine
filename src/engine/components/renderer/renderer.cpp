#include "renderer.hpp"

namespace Engine
{
  namespace Components
  {
    Renderer::Renderer(Scene::Node::NodePtr camera, int width, int height)
      : renderWidth_(width)
      , renderHeight_(height)
      , camera_(camera->component<Camera>())
      , gBufferShader_(
        Rendering::Shader::createFromStrings(
          get_gbuffer_vertex_shader(),
          get_gbuffer_fragment_shader()))
    {
      if (!camera_)
        throw std::invalid_argument(
          "Camera node doesn't contain a camera component.");

      if (!gBufferShader_.compile())
        throw std::logic_error("gBuffer shader " + std::string(
          gBufferShader_.get_compilation_info()));


      // Create the FBO
      glGenFramebuffers(1, &gFrameBuffer_);
      glBindFramebuffer(GL_FRAMEBUFFER, gFrameBuffer_);

      // gBuffer Textures
      glGenTextures(4, gTextures);
      for (unsigned int i = 0; i < 4; i++)
      {
        glBindTexture(GL_TEXTURE_2D, gTextures[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, renderWidth_, renderHeight_,
                     0, GL_RGB, GL_FLOAT, NULL);
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
                              GL_COLOR_ATTACHMENT2,
                              GL_COLOR_ATTACHMENT3};
      glDrawBuffers(4, DrawBuffers);

      GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

      if (Status != GL_FRAMEBUFFER_COMPLETE)
        throw std::logic_error("gBuffer framebuffer error.");

      // restore default FBO
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
    Renderer::toggle_debug(bool debug)
    {
      debug_ = debug;
    }

    const GLchar*
    Renderer::get_gbuffer_vertex_shader()
    {
      return "#version 330\n"
        "layout (location = 0) in vec3 Position;\n"
        "layout (location = 1) in vec3 Normal;\n"
        "layout (location = 2) in vec2 TexCoord;\n"
        "uniform mat4 model;\n"
        "uniform mat4 view;\n"
        "uniform mat4 projection;\n"
        "out vec2 TexCoord0;\n"
        "out vec3 Normal0;\n"
        "out vec3 WorldPos0;\n"
        "void main()\n"
        "{\n"
        "    vec4 worldPos  = model * vec4(Position, 1.0f);\n"
        "    gl_Position    = projection * view * worldPos;\n"
        "    TexCoord0      = TexCoord;\n"
        "    Normal0        = transpose(inverse(mat3(model))) * Normal;\n"
        "    WorldPos0      = worldPos.xyz;\n"
        "}\n\0";
    }

    const GLchar*
    Renderer::get_gbuffer_fragment_shader()
    {
      return "#version 330\n"
        "in vec2 TexCoord0;\n"
        "in vec3 Normal0;\n"
        "in vec3 WorldPos0;\n"
        "layout (location = 0) out vec3 WorldPosOut;\n"
        "layout (location = 1) out vec3 DiffuseOut;\n"
        "layout (location = 2) out vec3 NormalOut;\n"
        "layout (location = 3) out vec3 TexCoordOut;\n"
        "uniform sampler2D gColorMap;\n"
        "void main()\n"
        "{\n"
        "    WorldPosOut     = WorldPos0;\n"
        "    DiffuseOut      = texture(gColorMap, TexCoord0).xyz;\n"
        "    NormalOut       = normalize(Normal0);\n"
        "    TexCoordOut     = vec3(TexCoord0, 0.0);\n"
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
          GLuint program = gBufferShader_.get_program();
          GLint modelUni = glGetUniformLocation(program, "model");
          GLint viewUni = glGetUniformLocation(program, "view");
          GLint projectionUni = glGetUniformLocation(program, "projection");

          // Sends the view matrix
          glUniformMatrix4fv(viewUni, 1, GL_FALSE,
                             glm::value_ptr(camera_->get_view_matrix()));
          // Sends the projection
          glUniformMatrix4fv(projectionUni, 1, GL_FALSE,
                             glm::value_ptr(camera_->get_projection_matrix()));
          // Sends the model matrix
          glUniformMatrix4fv(modelUni, 1, GL_FALSE,
                             glm::value_ptr(transform->get_world_matrix()));

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
      gBufferShader_.use_shader();

      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, gFrameBuffer_);

      glClearColor(0.2f, 0.0f, 0.0f, 1.0f); // R - Quad
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      // Render models
      render(get_target());

      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glBindFramebuffer(GL_READ_FRAMEBUFFER, gFrameBuffer_);

      if (debug_)
      {
        GLint HalfWidth = (GLint)(renderWidth_ / 8.0f);
        GLint HalfHeight = (GLint)(renderHeight_ / 8.0f);

        glReadBuffer(GL_COLOR_ATTACHMENT0);
        glBlitFramebuffer(0, 0,
                          renderWidth_, renderHeight_,
                          0, renderHeight_,
                          HalfWidth, renderHeight_ - HalfHeight,
                          GL_COLOR_BUFFER_BIT, GL_LINEAR);

        glReadBuffer(GL_COLOR_ATTACHMENT1);
        glBlitFramebuffer(0, 0,
                          renderWidth_, renderHeight_,
                          0, renderHeight_ - HalfHeight,
                          HalfWidth, renderHeight_ - HalfHeight * 2,
                          GL_COLOR_BUFFER_BIT, GL_LINEAR);

        glReadBuffer(GL_COLOR_ATTACHMENT2);
        glBlitFramebuffer(0, 0,
                          renderWidth_, renderHeight_,
                          0, renderHeight_ - HalfHeight * 2,
                          HalfWidth, renderHeight_ - HalfHeight * 3,
                          GL_COLOR_BUFFER_BIT, GL_LINEAR);

        glReadBuffer(GL_COLOR_ATTACHMENT3);
        glBlitFramebuffer(0, 0,
                          renderWidth_, renderHeight_,
                          0, renderHeight_ - HalfHeight * 3,
                          HalfWidth, renderHeight_ - HalfHeight * 4,
                          GL_COLOR_BUFFER_BIT, GL_LINEAR);
      }
    }

  } // namespace Components
} // namespace Engine
