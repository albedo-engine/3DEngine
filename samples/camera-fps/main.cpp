#include <engine.hpp>
#include "../utils/glfw_freecam.hpp"

#include "SOIL/SOIL.h"

#include <shaders/get_shader.hpp>

#include <rendering/texture-cubemap.hpp>

#include <components/geometry/triangle.hpp>
#include <components/renderer/renderer.hpp>
#include <components/geometry/cube.hpp>
#include <components/material/material-pbr.hpp>
#include <components/material/material-skybox.hpp>
#include <shaders/formatted/skyboxVertex_glsl.h>
#include <shaders/formatted/skyboxFragment_glsl.h>

using namespace Engine;
using namespace Engine::Scene;
using namespace Engine::Components;
using namespace Engine::Rendering;

Texture2D::Texture2DPtr buildTexture()
{
  int width = 128;
  int height = 128;
  auto texture = Texture2D::create(width, height);

  unsigned char* img = SOIL_load_image("cat-128.png", &width, &height, 0, SOIL_LOAD_RGBA);
  if (img == NULL)
    throw std::invalid_argument("Image loading fail");

  texture->load(img);

  SOIL_free_image_data(img);

  return texture;
}

int main(int c, char** argv)
{
  int width  = 1000;
  int height = 800;

  GLFW_Freecam freecam(width, height, "Cube");

  // Initializes the engine
  Engine::Engine::initialize();

  // Creates the shader used to fill the GBuffer
  Shader::ShaderPtr shader = Shader::create(GET_SHADER(gbuffer_vs),
                                            GET_SHADER(gbuffer_fs));
  shader->compile();
  shader->addUniform({"uAlbedoFactor", "vec4"});
  shader->addUniform({"uAlbedoMap", "sampler2D"});

  //Material::MaterialPtr material = Material::create();
  auto cubeTexture = buildTexture();
  MaterialPBR::MaterialPBRPtr material = MaterialPBR::create();
  material->set_shader(shader);
  material->setColorFactor(glm::vec4(1.0, 0.0, 0.0, 1.0));
  material->setAlbedo(cubeTexture);

  // Create the cube node
  Node::NodePtr cube = Node::create("cube");
  cube->add_component(Transform::create());
  cube->component<Transform>()->translate(glm::vec3(0, 0, -4));
  cube->add_component(Cube::create());
  cube->add_component(material);

  // Create a camera with a renderer attached to it
  Node::NodePtr camera_node = Node::create("camera");
  camera_node->add_component(PerspectiveCamera::create(width, height));
  camera_node->add_component(Transform::create());
  camera_node->component<Transform>()->translate(glm::vec3(0, 0, 4));
  freecam.set_camera(camera_node);

  // Root node
  Node::NodePtr         root     = Node::create("root");
  Renderer::RendererPtr renderer = Renderer::create(camera_node, width, height);
  root->add_component(renderer);
  root->add_child(camera_node);
  root->add_child(cube);

  // Create some randomized lights
  //srand(time(0));
  for (int i = 0; i < 100; ++i)
  {
    // Light
    Node::NodePtr             light      = Node::create();
    PointLight::PointLightPtr pointlight = PointLight::create();
    pointlight->set_color(glm::vec3((rand() % 100) / 200.0f + 0.6f,
                                    (rand() % 100) / 200.0f + 0.6f,
                                    (rand() % 100) / 200.0f + 0.6f));

    //pointlight->set_color(glm::vec3(1.0, 1.0, 1.0));

    light->add_component(pointlight);

    // Position
    light->add_component(Transform::create());
    light->component<Transform>()->translate(
      glm::vec3((rand() % 100) / 50.0f * 3.0f,
                (rand() % 100) / 50.0f * 3.0f,
                (rand() % 100) / 50.0f * 3.0f));

    root->add_child(light);
  }

  /*PointLight::PointLightPtr pointlight = PointLight::create();
  pointlight->set_color(glm::vec3(1.0, 1.0, 1.0));
  Node::NodePtr             light      = Node::create();
  light->add_component(pointlight);
  light->add_component(Transform::create());
  light->component<Transform>()->translate(glm::vec3(0.0, 2.0, 0.0));
  root->add_child(light);*/

  while (!freecam.should_close())
  {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    freecam.pre_update();

    // Renders the scene from the given camera point of view
    renderer->display();

    freecam.post_update();
  }

  return 0;
}
