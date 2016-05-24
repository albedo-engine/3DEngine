#include "engine.hpp"
#include <GLFW/glfw3.h>

#include "components/transform/transform.hpp"
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
  glewExperimental = GL_TRUE;
  if (!glfwInit())
    throw 1;
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
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

  // Create a camera
  Node::NodePtr camera = Node::create("camera");

  // Create the triangle mesh
  Triangle::TrianglePtr triangle_mesh = Triangle::create();

  // Create the triangle node
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
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // Draws
    glfwSwapBuffers(window);
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
