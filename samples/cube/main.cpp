#include <GLFW/glfw3.h>
#include <iostream>

#include "engine.hpp"
#include "components/transform.hpp"

using namespace Engine;
using namespace Engine::Scene;

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

  Node::NodePtr root = std::shared_ptr<Node>(new Node("root"));
  Node::NodePtr camera = std::shared_ptr<Node>(new Node("camera"));
  Node::NodePtr cube = std::shared_ptr<Node>(new Node("cube"));
  cube->add_component(std::shared_ptr<Transform>(new Transform()));

  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
