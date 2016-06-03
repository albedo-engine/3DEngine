#include <engine.hpp>
#include <GLFW/glfw3.h>

#include <components/transform/transform.hpp>
#include <components/geometry/geometry.hpp>
#include <components/geometry/triangle.hpp>
#include <components/renderer/renderer.hpp>
#include <components/material/material.hpp>

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
  glewExperimental = GL_TRUE;
  if (!glfwInit())
    throw 1;
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  int width = 640;
  int height = 480;
  GLFWwindow* window = glfwCreateWindow(width, height, "Triangle Sample", NULL, NULL);

  if (!window)
  {
    glfwTerminate();
    throw 1;
  }
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, key_callback);

  // Define the viewport dimensions
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);

  // Initializes the engine
  Engine::Engine::initialize();


  // Create the triangle node
  Node::NodePtr triangle = Node::create("triangle");
  triangle->add_component(Transform::create());
  triangle->add_component(Triangle::create());
  triangle->add_component(Material::create());

  // Create a camera with a renderer attached to it
  Renderer::RendererPtr renderer = Renderer::create(width, height);
  Node::NodePtr camera = Node::create("camera");
  camera->add_component(renderer);

  // Link components in a single scene by adding them to a root node
  Node::NodePtr root = Node::create("root");
  root->add_child(camera);
  camera->add_child(triangle);

  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();

    renderer->display();

    glfwSwapBuffers(window);
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
