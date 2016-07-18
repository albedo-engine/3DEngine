#pragma once

#include <iostream>
#include <engine.hpp>
#include <GLFW/glfw3.h>

using namespace Engine;
using namespace Engine::Scene;

static void freecam_key_dispatch(GLFWwindow* window, int key, int scancode, int action, int mods);
static void freecam_mouse_dispatch(GLFWwindow* window, double xpos, double ypos);
static void freecam_error_callback(int error, const char* description);


class GLFW_Freecam
{
  public:
    GLFW_Freecam(int width, int height, const char* title);
    ~GLFW_Freecam();

  public:
    void pre_update();
    void post_update();
    bool should_close();

    void set_camera(Node::NodePtr camera_node);
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void mouse_callback(GLFWwindow* window, double xpos, double ypos);

  private:
    void init(int width, int height, const char* title);

    void update_camera_lookat(GLfloat x_offset, GLfloat y_offset);
    void update_camera_position();

  private:
    Node::NodePtr camera;

    GLfloat camera_yaw;
    GLfloat camera_pitch;

    double last_mouse_x;
    double last_mouse_y;

    GLfloat game_time;
    GLfloat last_frame;

    GLFWwindow* window;

    bool keys[512];
    bool init_mouse;
    

};
