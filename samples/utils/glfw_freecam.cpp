#include "glfw_freecam.hpp"

void freecam_key_dispatch(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  GLFW_Freecam* ptr = static_cast<GLFW_Freecam*>(glfwGetWindowUserPointer(window));
  ptr->key_callback(window, key, scancode, action, mods);

}
void freecam_mouse_dispatch(GLFWwindow* window, double xpos, double ypos)
{
  GLFW_Freecam* ptr = static_cast<GLFW_Freecam*>(glfwGetWindowUserPointer(window));
  ptr->mouse_callback(window, xpos, ypos);
}

void freecam_error_callback(int error, const char* description)
{
  std::cerr << "Error " << error << ": " << description;
}


GLFW_Freecam::GLFW_Freecam(int width, int height, const char* title)
            : camera(nullptr)
            , camera_yaw(0.0f)
            , camera_pitch(0.0f)
            , last_mouse_x(0.0f)
            , last_mouse_y(0.0f)
{
  this->init(width, height, title);
}

GLFW_Freecam::~GLFW_Freecam()
{
  glfwDestroyWindow(window);
  glfwTerminate();
}

void GLFW_Freecam::init(int width, int height, const char* title)
{
  if (!glfwInit())
    throw 1;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  window = glfwCreateWindow(width, height, title, NULL, NULL);

  if (!window)
  {
    glfwTerminate();
    throw 1;
  }

  glfwMakeContextCurrent(window);

  for (int i = 0; i < 512; ++i)
    keys[i] = false;
  
  this->last_mouse_x = width / 2;
  this->last_mouse_y = height / 2;
  this->init_mouse = true;

  // Events
  glfwSetKeyCallback(window, freecam_key_dispatch);
  glfwSetCursorPosCallback(window, freecam_mouse_dispatch);
  glfwSetErrorCallback(freecam_error_callback);

  // Disable cursor
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

  // Viewport dimension
  int vw_width, vw_height;
  glfwGetFramebufferSize(window, &vw_width, &vw_height);
  glViewport(0, 0, vw_width, vw_height);

  // Store this as a user pointer for callbacks usage
  glfwSetWindowUserPointer(window, this);
}

void
GLFW_Freecam::pre_update()
{

  GLfloat current_frame = glfwGetTime();
  this->game_time = current_frame - last_frame;
  this->last_frame = current_frame;

  glfwPollEvents();

  // Update the camera position
  this->update_camera_position();
}

void
GLFW_Freecam::post_update()
{
  // Post-render updates (buffers swap)
  glfwSwapBuffers(window);
}

bool
GLFW_Freecam::should_close()
{
  return glfwWindowShouldClose(window) == 1;
}

void
GLFW_Freecam::set_camera(Node::NodePtr camera_node)
{
  this->camera = camera_node;
}

void
GLFW_Freecam::update_camera_lookat(GLfloat x_offset, GLfloat y_offset)
{
  x_offset *= 0.5f;
  y_offset *= 0.5f;

  this->camera_yaw += x_offset;
  this->camera_pitch += y_offset;

  auto camera_transform = camera->component<Transform>();
  glm::quat quat = glm::angleAxis(glm::radians(-camera_pitch),
                                  glm::vec3(1, 0, 0));
  quat *= glm::angleAxis(glm::radians(camera_yaw), glm::vec3(0, 1, 0));
  camera_transform->rotateTo(quat);
}

void
GLFW_Freecam::update_camera_position()
{
  auto camera_transfrom = camera->component<Transform>();
  if (keys[GLFW_KEY_W])
    camera_transfrom->translate(game_time * 5.0f,
                                Transform::Direction::FORWARD);
  if (keys[GLFW_KEY_S])
    camera_transfrom->translate(game_time * 5.0f,
                                Transform::Direction::BACKWARD);
  if (keys[GLFW_KEY_A])
  {
    camera_transfrom->translate(game_time * 5.0f,
                                Transform::Direction::WESTWARD);
  }
  if (keys[GLFW_KEY_D])
    camera_transfrom->translate(game_time * 5.0f,
                                Transform::Direction::EASTWARD);
}

void
GLFW_Freecam::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);

  if (key < 0 || key >= 1024)
    return;

  // Updates the key dictionnary
  if (action == GLFW_PRESS)
    keys[key] = true;
  else if (action == GLFW_RELEASE)
    keys[key] = false;
}

void
GLFW_Freecam::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
  if (this->init_mouse)
  {
    this->last_mouse_x = xpos;
    this->last_mouse_y = ypos;
    this->init_mouse = false;
  }

  this->update_camera_lookat(xpos - last_mouse_x, last_mouse_y - ypos);

  last_mouse_x = xpos;
  last_mouse_y = ypos;

}
