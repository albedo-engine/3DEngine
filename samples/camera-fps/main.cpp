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
static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

static void update_camera();
static void update_camera_lookat(GLfloat x_offset, GLfloat y_offset);

// Global attributes
bool                keys[1024];               // Dictionnary allowing to know whether a key is pressed/released

Node::NodePtr       camera_node   = nullptr;  // Holds a pointer to the camera to make it move
GLfloat             camera_yaw    = 0.0f;
GLfloat             camera_pitch  = 0.0f;

GLfloat             last_mouse_x  = 0.0f;
GLfloat             last_mouse_y  = 0.0f;

bool                first         = true;

GLfloat             game_time     = 0.0f;     // Makes animations frame independant
GLfloat             last_frame    = 0.0f;     // Makes animations frame independant

int main()
{
  glfwSetErrorCallback(error_callback);
  glewExperimental = GL_TRUE;
  if (!glfwInit())
    throw 1;
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  int width = 800;
  int height = 600;
  GLFWwindow* window = glfwCreateWindow(width, height, "Triangle Sample", NULL, NULL);

  if (!window)
  {
    glfwTerminate();
    throw 1;
  }
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, key_callback);
  glfwSetCursorPosCallback(window, mouse_callback);

  // Define the viewport dimensions
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);
  last_mouse_x = width / 2;
  last_mouse_y = height / 2;

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
  renderer->toggle_debug(true);
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

static void update_camera_lookat(GLfloat x_offset, GLfloat y_offset)
{
  x_offset *= 0.5f;
  y_offset *= 0.5f;

  camera_yaw += x_offset;
  camera_pitch += y_offset;

  auto camera_transform = camera_node->component<Transform>();
  //glm::quat quat = glm::angleAxis(x_offset, glm::vec3(0, 1, 0));
  //camera_transform->rotate(quat);
  //quat = glm::angleAxis(y_offset, camera_transform->get_right());
  glm::quat quat = glm::angleAxis(glm::radians(-camera_pitch), glm::vec3(1,0,0));
  quat *= glm::angleAxis(glm::radians(camera_yaw), glm::vec3(0,1,0));
  camera_transform->rotate_to(quat);
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

static void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
  if (first)
  {
    last_mouse_x = xpos;
    last_mouse_y = ypos;
    first = false;
  }
  GLfloat x_offset = xpos - last_mouse_x;
  GLfloat y_offset = last_mouse_y - ypos;

  last_mouse_x = xpos;
  last_mouse_y = ypos;

  update_camera_lookat(x_offset, y_offset);
}