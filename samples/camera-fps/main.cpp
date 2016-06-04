#include <engine.hpp>
#include <GLFW/glfw3.h>

#include <components/geometry/triangle.hpp>
#include <components/renderer/renderer.hpp>
#include <components/geometry/cube.hpp>

using namespace Engine;
using namespace Engine::Scene;
using namespace Engine::Components;

static void error_callback(int error, const char* description);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

static void update_camera();

// Global attributes
Node::NodePtr camera_node = nullptr;  // Holds a pointer to the camera to make it move
GLfloat game_time         = 0.0f;     // Makes animations frame independant
GLfloat last_frame        = 0.0f;     // Makes animations frame independant
bool keys[1024];                      // Dictionnary allowing to know whether a key is pressed/released

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
  Node::NodePtr cube = Node::create("cube");
  cube->add_component(Transform::create());
  cube->add_component(Cube::create());
  cube->add_component(Material::create());

  // Create a camera with a renderer attached to it
  camera_node = Node::create("camera");
  camera_node->add_component(PerspectiveCamera::create(width, height));
  camera_node->add_component(Transform::create());
  camera_node->component<Transform>()->translate(glm::vec3(0, 0, 5));

  // Link components in a single scene by adding them to a root node
  Node::NodePtr root = Node::create("root");
  Renderer::RendererPtr renderer = Renderer::create(camera_node, width, height);
  root->add_component(renderer);
  root->add_child(camera_node);
  root->add_child(cube);

  while (!glfwWindowShouldClose(window))
  {
    GLfloat current_frame = glfwGetTime();
    game_time = current_frame - last_frame;
    last_frame = current_frame;

    // Updates GLFW events
    glfwPollEvents();

    // Sends data input to the update_camera function for processing
    update_camera();

    // Renders the scene from the given camera point of view
    renderer->display();

    glfwSwapBuffers(window);
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}

static void update_camera()
{
  auto camera_transfrom = camera_node->component<Transform>();
  if(keys[GLFW_KEY_W])
    camera_transfrom->translate(game_time * 5.0f, Transform::Direction::FORWARD);
  if(keys[GLFW_KEY_S])
    camera_transfrom->translate(game_time * 5.0f, Transform::Direction::BACKWARD);
  if(keys[GLFW_KEY_A])
    camera_transfrom->translate(game_time * 5.0f, Transform::Direction::WESTWARD);
  if(keys[GLFW_KEY_D])
    camera_transfrom->translate(game_time * 5.0f, Transform::Direction::EASTWARD);
}

static void error_callback(int error, const char* description)
{
  std::cerr << "Error " << error << ": " << description;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);

  // Updates the key dictionnary
  if (key < 0 || key >= 1024)
    return;

  if (action == GLFW_PRESS)
    keys[key] = true;
  else if (action == GLFW_RELEASE)
    keys[key] = false;
}