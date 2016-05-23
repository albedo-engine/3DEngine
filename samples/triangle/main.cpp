#include "engine.hpp"
#include <GLFW/glfw3.h>

#include "components/transform.hpp"
#include "components/geometry/geometry.hpp"
#include "components/geometry/triangle.hpp"

using namespace Engine;
using namespace Engine::Scene;
using namespace Engine::Components;

static void error_callback(int error, const char* description)
{
  std::cerr << "Error " << error << ": " << description;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

int main()
{
  glfwSetErrorCallback(error_callback);

  if (!glfwInit())
    throw 1;

  GLFWwindow* window = glfwCreateWindow(640, 480, "Triangle Sample", NULL, NULL);

  glfwSetKeyCallback(window, key_callback);

  if (!window)
  {
    glfwTerminate();
    throw 1;
  }

  // Create a camera
  Node::NodePtr camera = Node::create("camera");

  // Create the triangle
  Node::NodePtr triangle = Node::create("triangle");
  triangle->add_component(Transform::create(glm::vec3(0.f, 0.f, 0.f)));
  triangle->add_component(Triangle::create());

  // Link components in a single scene by adding them to a root node
  Node::NodePtr root = Node::create("root");
  root->add_child(camera);
  root->add_child(triangle);

  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
    // Refreshes screen
    // Draws
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
