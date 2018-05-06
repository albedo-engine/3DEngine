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

#include <scene/visitor/update-visitor.hpp>

using namespace Engine;
using namespace Engine::Scene;
using namespace Engine::Components;
using namespace Engine::Rendering;

Texture2D::Texture2DPtr buildTexture()
{
  int  width   = 128;
  int  height  = 128;
  auto texture = Texture2D::create(width, height);

  unsigned char* img = SOIL_load_image("../asset/cat.jpeg", &width, &height, 0,
                                       SOIL_LOAD_RGBA);
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
  auto                        cubeTexture = buildTexture();
  MaterialPBR::MaterialPBRPtr material    = MaterialPBR::create();
  material->setShader(shader);
  material->setColorFactor(glm::vec4(1.0, 0.0, 0.0, 1.0));
  material->setAlbedo(cubeTexture);

  // Create the cube node
  Node::NodePtr cube = Node::create("cube");
  cube->addComponent(Transform::create());
  cube->component<Transform>()->rotate(90.0, glm::vec3(1, 0, 0));
  cube->addComponent(Cube::create());
  cube->addComponent(material);

  Node::NodePtr dummyNode = Node::create("dummy");

  // Create the cube node
  Node::NodePtr cube2 = Node::create("cube2");
  cube2->addComponent(Transform::create());
  cube2->component<Transform>()->translate(glm::vec3(0, 1, 0));
  cube2->addComponent(Cube::create());
  cube2->addComponent(material);

  // Create a camera with a renderer attached to it
  Node::NodePtr camera_node = Node::create("camera");
  camera_node->addComponent(PerspectiveCamera::create(width, height));
  camera_node->addComponent(Transform::create());
  camera_node->component<Transform>()->translate(glm::vec3(0, 0, 4));
  freecam.set_camera(camera_node);

  // Build scene graph here
  dummyNode->addChild(cube2);
  //cube->addChild(cube2);
  cube->addChild(dummyNode);

  // Root node
  Node::NodePtr         root     = Node::create("root");
  Renderer::RendererPtr renderer = Renderer::create(camera_node, width, height);
  root->addChild(cube);
  root->addComponent(renderer);
  root->addChild(camera_node);

  cube->addUpdateCallback([](Node::NodePtr thisPtr) {

      auto t = thisPtr->component<Transform>();
      if (t != nullptr)
      {
        //t->translate(glm::vec3(0.1, 0.0, 0.0));
      }

      return true;
  });

  auto updateVisitor = UpdateVisitor::create();

  // Create some randomized lights
  srand(time(0));
  for (int i = 0; i < 100; ++i)
  {
    // Light
    Node::NodePtr             light      = Node::create();
    PointLight::PointLightPtr pointlight = PointLight::create();
    pointlight->setColor(glm::vec3((rand() % 100) / 200.0f + 0.6f,
                                   (rand() % 100) / 200.0f + 0.6f,
                                   (rand() % 100) / 200.0f + 0.6f));

    //pointlight->set_color(glm::vec3(1.0, 1.0, 1.0));

    light->addComponent(pointlight);

    // Position
    light->addComponent(Transform::create());
    light->component<Transform>()->translate(
      glm::vec3((rand() % 100) / 50.0f * 2.0f,
                (rand() % 100) / 50.0f * 2.0f,
                (rand() % 100) / 50.0f * 2.0f));

    root->addChild(light);
  }

  while (!freecam.should_close())
  {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    freecam.pre_update();

    // Updates the scene
    updateVisitor->visit(root);

    // Renders the scene
    renderer->display();

    freecam.post_update();
  }

  return 0;
}
