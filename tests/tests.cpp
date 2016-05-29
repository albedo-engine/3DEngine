#include "utils/test_utils.hpp"

#include "engine.hpp"

using namespace Engine;
using namespace Engine::Scene;
using namespace Engine::Components;

void test_transform()
{
  Node::NodePtr parent = Node::create("parent");
  parent->add_component(Transform::create());

  Node::NodePtr child = Node::create();

  ASSERT(parent->component<Transform>() != nullptr, "get existing component");
  ASSERT(parent->component<Geometry>() == nullptr, "get non-existing component");
  ASSERT(parent->component<Transform>()->get_local_position() == glm::vec3(0, 0, 0), "check local position");
  ASSERT(parent->get_parent() == nullptr, "check for null parents");
  ASSERT(parent->component<Transform>()->get_world_position() == glm::vec3(0, 0, 0), "check world position");

  // Checks position without parent
  parent->component<Transform>()->translate(glm::vec3(5, 0, 0));
  ASSERT(parent->component<Transform>()->get_local_position() == glm::vec3(5, 0, 0), "check local position");
  ASSERT(parent->component<Transform>()->get_world_position() == glm::vec3(5, 0, 0), "check world position");

  // Checks position before adding parent
  child->add_component(Transform::create());
  child->component<Transform>()->translate(glm::vec3(0, 1, 0));
  ASSERT(child->component<Transform>()->get_local_position() == glm::vec3(0, 1, 0), "check local position");
  ASSERT(child->component<Transform>()->get_world_position() == glm::vec3(0, 1, 0), "check world position");

  // Checks position relative to parent
  parent->add_child(child);
  ASSERT(child->component<Transform>()->get_local_position() == glm::vec3(0, 1, 0), "check local position");
  ASSERT(child->component<Transform>()->get_world_position() == glm::vec3(5, 1, 0), "check world position");
}

void test_components()
{
  // Executes the test suite on the Transform class
  test_transform();
}

void test_node()
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
  LAUNCH(test_node);
  LAUNCH(test_components);
  LAUNCH(test_camera);

  return 0;
}
