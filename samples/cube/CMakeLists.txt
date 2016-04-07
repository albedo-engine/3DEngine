add_executable(Cube
  main.cpp
)

target_link_libraries(Cube LINK_PUBLIC
  Engine
  GLEW glfw3 GL X11 Xi Xrandr Xxf86vm Xinerama Xcursor rt m pthread dl
)
