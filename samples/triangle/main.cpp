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

  GLFWwindow* window = glfwCreateWindow(640, 480, "Cube Sample", NULL, NULL);

  glfwSetKeyCallback(window, key_callback);

  if (!window)
  {
    glfwTerminate();
    throw 1;
  }

  auto root = Node::create("root");
  auto camera = Node::create("camera");
  auto triangle = Node::create("triangle");
  auto triangle_geometry = Triangle::create();
  //triangle->add_component(triangle_geometry);

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
