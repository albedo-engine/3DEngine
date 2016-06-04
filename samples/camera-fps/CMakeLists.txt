set(SAMPLE_LIST ${SAMPLE_LIST} triangle PARENT_SCOPE)

add_executable(camera-fps
  main.cpp
)

target_link_libraries(camera-fps LINK_PUBLIC
  engine
  GLEW glfw3 GL X11 Xi Xrandr Xxf86vm Xinerama Xcursor rt m pthread dl
)
