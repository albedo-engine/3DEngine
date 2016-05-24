#include "utils/test_utils.hpp"

#include "engine.hpp"

using namespace Engine;
using namespace Engine::Scene;
using namespace Engine::Components;

void test_components()
{
  Node::NodePtr parent = Node::create("parent");
  Node::NodePtr child = Node::create();

  parent->add_child(child);

  ASSERT(parent->get_child_at(0) == child, "get_child_at");
  ASSERT(parent->has_child(child), "has_child");
}

void test_camera()
{
  PerspectiveCamera::PerspectiveCameraPtr camera = PerspectiveCamera::create();

  ASSERT(camera->get_fov() == 45.0f, "get_fov");
  ASSERT(camera->get_fov() != 90.0f, "get_fov");

  camera->set_fov(90.0f);

  ASSERT(camera->get_fov() == 90.0f, "set_fov");
}

int main()
{
  // Tests for components
  LAUNCH(test_components);
  LAUNCH(test_camera);

  return 0;
}
