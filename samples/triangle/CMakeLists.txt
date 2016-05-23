set(SAMPLE_LIST ${SAMPLE_LIST} triangle PARENT_SCOPE)

add_executable(triangle
  main.cpp
)

target_link_libraries(triangle LINK_PUBLIC
  engine
  GLEW glfw3 GL X11 Xi Xrandr Xxf86vm Xinerama Xcursor rt m pthread dl
)
