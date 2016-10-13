#include "utils/test_utils.hpp"

#include "engine.hpp"
#include <components/component-factory.hpp>
#include <components/light/pointlight.hpp>

using namespace Engine;
using namespace Engine::Scene;
using namespace Engine::Components;
using namespace Engine::Data;

void test_transform()
{
  Node::NodePtr parent = Node::create("parent");
  parent->add_component(Transform::create());

  Node::NodePtr child = Node::create();

  ASSERT(parent->component<Transform>() != nullptr, "get existing component");
  ASSERT(parent->component<Geometry>() == nullptr,
         "get non-existing component");
  ASSERT(
    parent->component<Transform>()->get_local_position() == glm::vec3(0, 0, 0),
    "check local position");
  ASSERT(parent->get_parent() == nullptr, "check for null parents");
  ASSERT(
    parent->component<Transform>()->get_world_position() == glm::vec3(0, 0, 0),
    "check world position");

  // Checks position without parent
  parent->component<Transform>()->translate(glm::vec3(5, 0, 0));
  ASSERT(
    parent->component<Transform>()->get_local_position() == glm::vec3(5, 0, 0),
    "check local position");
  ASSERT(
    parent->component<Transform>()->get_world_position() == glm::vec3(5, 0, 0),
    "check world position");

  // Checks position before adding parent
  child->add_component(Transform::create());
  child->component<Transform>()->translate(glm::vec3(0, 1, 0));
  ASSERT(
    child->component<Transform>()->get_local_position() == glm::vec3(0, 1, 0),
    "check local position");
  ASSERT(
    child->component<Transform>()->get_world_position() == glm::vec3(0, 1, 0),
    "check world position");

  // Checks position relative to parent
  parent->add_child(child);
  ASSERT(
    child->component<Transform>()->get_local_position() == glm::vec3(0, 1, 0),
    "check local position");
  ASSERT(
    child->component<Transform>()->get_world_position() == glm::vec3(5, 1, 0),
    "check world position");

  // Check centered rotation
  Node::NodePtr rotate_node = Node::create("rotate_node");
  rotate_node->add_component(Transform::create());
  rotate_node->component<Transform>()->rotate(90.0, glm::vec3(0.0, 1.0, 0.0));
  glm::vec3 dir = rotate_node->component<Transform>()->get_direction();
  ASSERT(glm::abs(dir[0] - 1.0) <= 0.00001, "check center rotation");
  ASSERT(glm::abs(dir[1] - 0.0) <= 0.00001, "check center rotation");
  ASSERT(glm::abs(dir[2] - 0.0) <= 0.00001, "check center rotation");
  rotate_node->component<Transform>()->rotate(-90.0f, glm::vec3(0.0, 1.0, 0.0));
  dir = rotate_node->component<Transform>()->get_direction();
  ASSERT(glm::abs(dir[0] - 0.0) <= 0.00001, "check center reverse rotation");
  ASSERT(glm::abs(dir[1] - 0.0) <= 0.00001, "check center reverse rotation");
  ASSERT(glm::abs(dir[2] + 1.0) <= 0.00001, "check center reverse rotation");

  // Check rotation after translation
  rotate_node->component<Transform>()->translate(glm::vec3(1.0f, 1.0f, -1.0f));
  rotate_node->component<Transform>()->rotate(-90.0f, glm::vec3(0.0, 1.0, 0.0));
  dir = rotate_node->component<Transform>()->get_direction();
  ASSERT(glm::abs(dir[0] + 1.0f) <= 0.00001, "check center reverse rotation");
  ASSERT(glm::abs(dir[1] - 0.0f) <= 0.00001, "check center reverse rotation");
  ASSERT(glm::abs(dir[2] - 0.0f) <= 0.00001, "check center reverse rotation");

  // Check for right vector
  glm::vec3 right = rotate_node->component<Transform>()->get_right();
  ASSERT(glm::abs(right[0] - 0.0f) <= 0.00001, "check right vector");
  ASSERT(glm::abs(right[1] - 0.0f) <= 0.00001, "check right vector");
  ASSERT(glm::abs(right[2] + 1.0f) <= 0.00001, "check right vector");

  // Check for up vector
  glm::vec3 up = rotate_node->component<Transform>()->get_up();
  ASSERT(glm::abs(up[0] - 0.0f) <= 0.00001, "check up vector");
  ASSERT(glm::abs(up[1] - 1.0f) <= 0.00001, "check up vector");
  ASSERT(glm::abs(up[2] - 0.0f) <= 0.00001, "check up vector");

  // Check centered look_at function
  Node::NodePtr look_at_node = Node::create("look_at_node");
  look_at_node->add_component(Transform::create());
  look_at_node->component<Transform>()->look_at(glm::vec3(0.0f, 1.0f, 0.0f));
  dir = look_at_node->component<Transform>()->get_direction();
  ASSERT(glm::abs(dir[0] - 0.0f) <= 0.00001, "check center look_at");
  ASSERT(glm::abs(dir[1] - 1.0f) <= 0.00001, "check center look_at");
  ASSERT(glm::abs(dir[2] - 0.0f) <= 0.00001, "check center look_at");

  look_at_node->component<Transform>()->look_at(glm::vec3(0.0f, -1.0f, 0.0f));
  dir = look_at_node->component<Transform>()->get_direction();
  ASSERT(glm::abs(dir[0] - 0.0f) <= 0.00001, "check center look_at");
  ASSERT(glm::abs(dir[1] + 1.0f) <= 0.00001, "check center look_at");
  ASSERT(glm::abs(dir[2] - 0.0f) <= 0.00001, "check center look_at");
}

void test_material()
{
  auto mat = ComponentFactory::instance()->component<Material>();
  ASSERT(mat->get_material_id() == 0, "check material id");
  auto mat2 = ComponentFactory::instance()->component<Material>();
  ASSERT(mat2->get_material_id() == 1, "check material id");
}

void test_components()
{
  // Executes the test suite on the Transform class
  test_transform();
  // Executes the test suite of the Material class
  test_material();
}

void test_node()
{
  Node::NodePtr parent = Node::create("parent");
  Node::NodePtr child = Node::create();

  parent->add_child(child);

  ASSERT(parent->has_child(child), "has_child");
}

void test_camera()
{
  PerspectiveCamera::PerspectiveCameraPtr camera = PerspectiveCamera::create(
    800.f, 600.f);

  ASSERT(camera->get_fov() == 45.0f, "get_fov");
  ASSERT(camera->get_fov() != 90.0f, "get_fov");

  camera->set_fov(90.0f);

  ASSERT(camera->get_fov() == 90.0f, "set_fov");
}

void test_store()
{
  auto pointlight = ComponentFactory::instance()->component<PointLight>();
  ASSERT(pointlight->get_color() == glm::vec3(), "test store with light");

  pointlight->set_color(glm::vec3(0.5f, 0.0f, 0.1f));
  auto color = pointlight->get_color();
  ASSERT(color.r == 0.5f && color.g == 0.0f && color.b == 0.1f, "test store with light");
}

int main()
{
  // Tests for components
  LAUNCH(test_node);
  LAUNCH(test_components);
  LAUNCH(test_camera);
  LAUNCH(test_store);

  return 0;
}
