#include <engine.hpp>
#include "../utils/glfw_freecam.hpp"

#include <components/geometry/triangle.hpp>
#include <components/renderer/renderer.hpp>
#include <components/geometry/cube.hpp>

using namespace Engine;
using namespace Engine::Scene;
using namespace Engine::Components;


int main()
{
  int width = 1000;
  int height = 800;

  GLFW_Freecam freecam(width, height, "Cube");

  // Initializes the engine
  Engine::Engine::initialize();

  // Create the triangle node
  Node::NodePtr cube = Node::create("cube");
  cube->add_component(Transform::create());
  cube->add_component(Cube::create());
  cube->add_component(Material::create());

  // Create a camera with a renderer attached to it
  Node::NodePtr camera_node = Node::create("camera");
  camera_node->add_component(PerspectiveCamera::create(width, height));
  camera_node->add_component(Transform::create());
  camera_node->component<Transform>()->translate(glm::vec3(0, 0, 5));
  freecam.set_camera(camera_node);

  // Root node
  Node::NodePtr root = Node::create("root");
  Renderer::RendererPtr renderer = Renderer::create(camera_node, width, height);
  root->add_component(renderer);
  root->add_child(camera_node);
  root->add_child(cube);

  // Create some randomized lights
  srand(time(0));
  for (int i = 0; i < 32; ++i)
  {
    // Light
    Node::NodePtr light = Node::create();
    PointLight::PointLightPtr pointlight = PointLight::create();
    pointlight->set_color(glm::vec3((rand() % 100) / 200.0f + 0.6f,
                                    (rand() % 100) / 200.0f + 0.6f,
                                    (rand() % 100) / 200.0f + 0.6f));
    light->add_component(pointlight);

    // Position
    light->add_component(Transform::create());
    light->component<Transform>()->translate(glm::vec3((rand() % 100) / 50.0f * 3.0f,
                                                       (rand() % 100) / 50.0f * 3.0f,
                                                       (rand() % 100) / 50.0f * 3.0f));

    root->add_child(light);
  }


  while (!freecam.should_close())
  {
    freecam.pre_update();

    // Renders the scene from the given camera point of view
    renderer->display();

    freecam.post_update();
  }

  return 0;
}
